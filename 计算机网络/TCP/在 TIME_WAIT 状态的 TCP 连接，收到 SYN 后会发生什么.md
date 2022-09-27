「在 TCP 正常挥手过程中，处于 TIME_WAIT 状态的连接，收到相同四元组的 SYN 后会发生什么？」

* SYN 的「序列号和时间戳」是否合法，因为处于 TIME_WAIT 状态的连接收到 SYN 后，会判断 SYN 的「序列号和时间戳」是否合法，
* 然后根据判断结果的不同做不同的处理。

先跟大家说明下， 什么是「合法」的 SYN？

合法 SYN：客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要大，并且 SYN 的「时间戳」比服务端「最后收到的报文的时间戳」要大。
非法 SYN：客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要小，或者 SYN 的「时间戳」比服务端「最后收到的报文的时间戳」要小。
上面 SYN 合法判断是基于双方都开启了 TCP 时间戳机制的场景，如果双方都没有开启 TCP 时间戳机制，则 SYN 合法判断如下：

合法 SYN：客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要大。
非法 SYN：客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要小。
#收到合法 SYN
如果处于 TIME_WAIT 状态的连接收到「合法的 SYN 」后，就会重用此四元组连接，跳过 2MSL 而转变为 SYN_RECV 状态，接着就能进行建立连接过程。


#### 处于 TIME_WAIT 状态的连接，收到 RST 会断开连接吗？

会不会断开，关键看 net.ipv4.tcp_rfc1337 这个内核参数（默认情况是为 0）：

如果这个参数设置为 0， 收到 RST 报文会提前结束 TIME_WAIT 状态，释放连接。
如果这个参数设置为 1， 就会丢掉 RST 报文。
源码处理如下：
```c
enum tcp_tw_status
tcp_timewait_state_process(struct inet_timewait_sock *tw, struct sk_buff *skb,
const struct tcphdr *th)
{
....
//rst报文的时间戳没有发生回绕
if (!paws_reject &&
(TCP_SKB_CB(skb)->seq == tcptw->tw_rcv_nxt &&
(TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq || th->rst))) {

      //处理rst报文
      if (th->rst) {
        //不开启这个选项，当收到 RST 时会立即回收tw，但这样做是有风险的
        if (twsk_net(tw)->ipv4.sysctl_tcp_rfc1337 == 0) {
          kill:
          //删除tw定时器，并释放tw
          inet_twsk_deschedule_put(tw);
          return TCP_TW_SUCCESS;
        }
      } else {
        //将 TIMEWAIT 状态的持续时间重新延长
        inet_twsk_reschedule(tw, TCP_TIMEWAIT_LEN);
      }

      ...
      return TCP_TW_SUCCESS;
    }
}
```
TIME_WAIT 状态收到 RST 报文而释放连接，这样等于跳过 2MSL 时间，这么做还是有风险。

sysctl_tcp_rfc1337 这个参数是在 rfc 1337 文档提出来的，目的是避免因为 TIME_WAIT 状态收到 RST 报文而跳过 2MSL 的时间，文档里也给出跳过 2MSL 时间会有什么潜在问题。

TIME_WAIT 状态之所以要持续 2MSL 时间，主要有两个目的：

**防止历史连接中的数据，被后面相同四元组的连接错误的接收；**
**保证「被动关闭连接」的一方，能被正确的关闭；**
详细的为什么要设计 TIME_WAIT 状态，我在这篇有详细说明：如果 TIME_WAIT 状态持续时间过短或者没有，会有什么问题？(opens new window)

虽然 TIME_WAIT 状态持续的时间是有一点长，显得很不友好，但是它被设计来就是用来避免发生乱七八糟的事情。

《UNIX网络编程》一书中却说道：TIME_WAIT 是我们的朋友，它是有助于我们的，不要试图避免这个状态，而是应该弄清楚它。

所以，我个人觉得将 net.ipv4.tcp_rfc1337 设置为 1 会比较安全。

#### 总结
在 TCP 正常挥手过程中，处于 TIME_WAIT 状态的连接，收到相同四元组的 SYN 后会发生什么？

如果双方开启了时间戳机制：

如果客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要大，并且SYN 的「时间戳」比服务端「最后收到的报文的时间戳」要大。那么就会重用该四元组连接，跳过 2MSL 而转变为 SYN_RECV 状态，接着就能进行建立连接过程。
如果客户端的 SYN 的「序列号」比服务端「期望下一个收到的序列号」要小，或者SYN 的「时间戳」比服务端「最后收到的报文的时间戳」要小。那么就会再回复一个第四次挥手的 ACK 报文，客户端收到后，发现并不是自己期望收到确认号，就回 RST 报文给服务端。
在 TIME_WAIT 状态，收到 RST 会断开连接吗？

如果 net.ipv4.tcp_rfc1337 参数为 0，则提前结束 TIME_WAIT 状态，释放连接。
如果 net.ipv4.tcp_rfc1337 参数为 1，则会丢掉该 RST 报文。