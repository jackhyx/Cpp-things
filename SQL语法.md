

### 1873. 计算特殊奖金

```mysql
SELECT employee_id,
(CASE WHEN MOD(employee_id,2)!=0 AND LEFT(name,1)!='M' THEN salary
      WHEN MOD(employee_id,2)=0 OR LEFT(name,1)='M' THEN 0
      END) bonus
FROM Employees
ORDER BY employee_id
```

* MySQL IF 根据表达式的某个条件或值结果来执行一组 SQL 语句。
语法结构如下：
IF(expr,v1,v2)
其中：表达式 expr 得到不同的结果，当 expr 为真是返回 v1 的值，否则返回 v2.

* Mod(a,b) 在sql中的意思是 a / b 的余数 # 基础用法：如果id需要是偶数或者奇数时就可以使用mod。
mod(id,2)=1 是指id是奇数。
mod(id,2)=0 是指id是偶数。

```mysql
SELECT
employee_id,
IF(MOD(employee_id,2)!=0 AND LEFT(name,1)!='M',salary,0) bonus
FROM Employees
ORDER BY employee_id
```
CASE配合WHEN,THEN判断，LEFT和’=‘判断，MOD取余
CASE配合WHEN,THEN使用，WHEN后接条件，THEN后接符合条件返回的内容 ，有多个条件时使用
需要用ELSE返回以上条件都不成立时返回的内容，最后以END`结尾
```mysql
SELECT
employee_id,
CASE
WHEN MOD(employee_id,2)!=0 AND LEFT(name,1)!='M' THEN salary
WHEN MOD(employee_id,2)=0 OR LEFT(name,1)='M' THEN 0
ELSE 0 -- 这里ELSE可以省略
END AS bonus
FROM Employees
ORDER BY employee_id
```

### 627. 变更性别
```mysql
UPDATE salary
SET
    sex = CASE sex
        WHEN "m" THEN "f"
        ELSE "m"
    END;
```

### 196. 删除重复的电子邮箱
编写一个 SQL 删除语句来 删除 所有重复的电子邮件，只保留一个id最小的唯一电子邮件。 
* 从查询结果中DELETE
```mysql
DELETE p1.* FROM Person p1,
    Person p2
WHERE
    p1.Email = p2.Email AND p1.Id > p2.Id

```

### 1667. 修复表中的名字
编写一个 SQL 查询来修复名字，使得只有第一个字符是大写的，其余都是小写的。

返回按 user_id 排序的结果表。
```mysql
SELECT user_id,
    CONCAT(UPPER(LEFT(name, 1)), LOWER(SUBSTR(name, 2))) name
FROM Users
ORDER BY
    user_id
```
* CONCAT 用来拼接字符串 
* LEFT 从左边截取字符
* RIGHT 从右边截取字符
* UPPER 变为大写
* LOWER 变为小写
* LENGTH 获取字符串长度
* substr(string,pos,end)这个函数不填入end就是取pos位置及其之后所有的字符。

### 1484. 按日期分组销售产品
编写一个 SQL 查询来查找每个日期、销售的不同产品的数量及其名称。 DISTINCT去重
每个日期的销售产品名称应按词典序排列。
返回按sell_date 排序的结果表。
查询结果格式如下例所示。

```mysql
SELECT sell_date,
       COUNT(DISTINCT product) num_sold,
       GROUP_CONCAT(DISTINCT product) products
FROM Activities
GROUP BY sell_date
```
连接group by的结果集时，可以指定自定义的分隔符，不指定的情况下，默认是 ',' GROUP_CONCAT(DISTINCT product ORDER BY product ASC SEPARATOR ',')
### 1527. 患某种疾病的患者
写一条SQL 语句，查询患有 I 类糖尿病的患者ID （patient_id）、患者姓名（patient_name）以及其患有的所有疾病代码（conditions）。I 类糖尿病的代码总是包含前缀DIAB1。
![img_1.png](img_1.png)
```mysql
SELECT *
FROM Patients 
where conditions like 'DIAB1%' or conditions like '% DIAB1%'
```
转义字符 \b 表示单词的边界，即空白字符或文本的开头或结尾

```mysql
SELECT *
FROM Patients
WHERE conditions REGEXP '\\bDIAB1'
------------------------------------------------
SELECT * 
FROM Patients
WHERE conditions REGEXP '\\bDIAB1.*\\b'; 
```
```mysql
SELECT *
FROM Patients
WHERE conditions REGEXP ' DIAB1|^DIAB1';
```

### 1965. 丢失信息的雇员
写出一个查询语句，找到所有 丢失信息 的雇员id。当满足下面一个条件时，就被认为是雇员的信息丢失：

雇员的 姓名 丢失了，或者
雇员的 薪水信息 丢失了，或者
返回这些雇员的id employee_id，从小到大排序。
雇员的姓名丢失了或者雇员的薪水信息丢失，都会导致employee_id 在 employees 和salaries 的并集表里面仅出现一次

union 和 union all都可以起到关联结果集的作用,
union 会自动去除关联的两个结果集中的重复数据
union all 不会主动去除两个结果集中的重复数据,会展示所有的数据


```mysql
SELECT employee_id 
FROM 
    (
    SELECT employee_id FROM employees
    UNION ALL 
    SELECT employee_id FROM salaries
) as t
GROUP BY employee_id
HAVING count(employee_id) = 1
ORDER BY employee_id;
```
```mysql
SELECT employee_id
FROM employees
    WHERE employee_id NOT IN (SELECT employee_id FROM salaries)
UNION 
SELECT employee_id 
FROM salaries
WHERE employee_id NOT IN (SELECT employee_id FROM employees)
ORDER BY employee_id
```


### 1795. 每个产品在不同商店的价格
输入：
Products table:
+------------+--------+--------+--------+
| product_id | store1 | store2 | store3 |
+------------+--------+--------+--------+
| 0          | 95     | 100    | 105    |
| 1          | 70     | null   | 80     |
+------------+--------+--------+--------+
输出：
+------------+--------+-------+
| product_id | store  | price |
+------------+--------+-------+
| 0          | store1 | 95    |
| 0          | store2 | 100   |
| 0          | store3 | 105   |
| 1          | store1 | 70    |
| 1          | store3 | 80    |
+------------+--------+-------+
* 列转行
```mysql
SELECT product_id, 'store1' store, store1 price FROM products WHERE store1 IS NOT NULL
UNION
SELECT product_id, 'store2' store, store2 price FROM products WHERE store2 IS NOT NULL
UNION
SELECT product_id, 'store3' store, store3 price FROM products WHERE store3 IS NOT NULL
```
* 行转列
```mysql
SELECT 
  product_id,
  SUM(IF(store = 'store1', price, NULL)) 'store1',
  SUM(IF(store = 'store2', price, NULL)) 'store2',
  SUM(IF(store = 'store3', price, NULL)) 'store3' 
FROM
  Products1 
GROUP BY product_id 

```


### 608. 树节点
给定一个表 tree，id 是树节点的编号， p_id 是它父节点的 id 。

+----+------+
| id | p_id |
+----+------+
| 1  | null |
| 2  | 1    |
| 3  | 1    |
| 4  | 2    |
| 5  | 2    |
+----+------+
树中每个节点属于以下三种类型之一：

叶子：如果这个节点没有任何孩子节点。
根：如果这个节点是整棵树的根，即没有父节点。
内部节点：如果这个节点既不是叶子节点也不是根节点。

+----+------+
| id | Type |
+----+------+
| 1  | Root |
| 2  | Inner|
| 3  | Leaf |
| 4  | Leaf |
| 5  | Leaf |
+----+------+

```mysql
select
    id,
    case when p_id is null then "Root"
         when id not in (select p_id from tree where p_id is not null) then "Leaf"
         else "Inner"
    end as Type
from
    tree
```
```mysql
# Write your MySQL query statement below
SELECT id,
    CASE
        WHEN p_id is NULL THEN 'Root'
        WHEN id in(SELECT p_id FROM tree) THEN 'Inner'
        ELSE 'Leaf' 
    END TYPE
FROM tree

```

### 176. 第二高的薪水
方法一：使用子查询和 LIMIT 子句
算法

将不同的薪资按降序排序，然后使用 LIMIT 子句获得第二高的薪资。
然而，如果没有这样的第二最高工资，这个解决方案将被判断为 “错误答案”，因为本表可能只有一项记录。为了克服这个问题，我们可以将其作为临时表。
```mysql
SELECT DISTINCT
    Salary AS SecondHighestSalary
FROM
    Employee
ORDER BY Salary DESC
LIMIT 1 OFFSET 1
```


```mysql
SELECT
    (SELECT DISTINCT
            Salary
        FROM
            Employee
        ORDER BY Salary DESC
        LIMIT 1 OFFSET 1) AS SecondHighestSalary

```
方法二：使用 IFNULL 和 LIMIT 子句
解决 “NULL” 问题的另一种方法是使用 “IFNULL” 函数，如下所示。
```mysql
SELECT
    IFNULL(
      (SELECT DISTINCT Salary
       FROM Employee
       ORDER BY Salary DESC
        LIMIT 1 OFFSET 1),
    NULL) AS SecondHighestSalary
```
### 175. 组合两个表
Person表:
+----------+----------+-----------+
| personId | lastName | firstName |
+----------+----------+-----------+
| 1        | Wang     | Allen     |
| 2        | Alice    | Bob       |
+----------+----------+-----------+
Address表:
+-----------+----------+---------------+------------+
| addressId | personId | city          | state      |
+-----------+----------+---------------+------------+
| 1         | 2        | New York City | New York   |
| 2         | 3        | Leetcode      | California |
+-----------+----------+---------------+------------+
输出:
+-----------+----------+---------------+----------+
| firstName | lastName | city          | state    |
+-----------+----------+---------------+----------+
| Allen     | Wang     | Null          | Null     |
| Bob       | Alice    | New York City | New York |
+-----------+----------+---------------+----------+
解释:
地址表中没有 personId = 1 的地址，所以它们的城市和州返回 null。
addressId = 1 包含了 personId = 2 的地址信息。

```mysql
SELECT firstName, lastName, city, state  
FROM Person LEFT JOIN Address
on Person.personId = Address.personId 
```
inner join：2表值都存在
outer join：附表中值可能存在null的情况。
总结：
①A inner join B：取交集
②A left join B：取A全部，B没有对应的值，则为null
③A right join B：取B全部，A没有对应的值，则为null
④A full outer join B：取并集，彼此没有对应的值为null
上述4种的对应条件，在on后填写。
### 1581. 进店却未进行过交易的顾客
输入:
Visits
+----------+-------------+
| visit_id | customer_id |
+----------+-------------+
| 1        | 23          |
| 2        | 9           |
| 4        | 30          |
| 5        | 54          |
| 6        | 96          |
| 7        | 54          |
| 8        | 54          |
+----------+-------------+
Transactions
+----------------+----------+--------+
| transaction_id | visit_id | amount |
+----------------+----------+--------+
| 2              | 5        | 310    |
| 3              | 5        | 300    |
| 9              | 5        | 200    |
| 12             | 1        | 910    |
| 13             | 2        | 970    |
+----------------+----------+--------+
输出:
+-------------+----------------+
| customer_id | count_no_trans |
+-------------+----------------+
| 54          | 2              |
| 30          | 1              |
| 96          | 1              |
+-------------+----------------+
```mysql
SELECT customer_id, COUNT(customer_id) count_no_trans
FROM Visits v
LEFT JOIN 
Transactions t
ON v.visit_id = t.visit_id
WHERE t.visit_id is NULL
GROUP BY customer_id
```