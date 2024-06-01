-- https://leetcode.com/problems/employees-earning-more-than-their-managers/

DROP TABLE IF EXISTS Employee;

CREATE TABLE Employee(
  id INT,
  name VARCHAR,
  salary INT,
  managerid INT
);

INSERT INTO Employee(id, name, salary, managerid) VALUES (1, 'Joe', 70000, 3);
INSERT INTO Employee(id, name, salary, managerid) VALUES (2, 'Henry', 80000, 4);
INSERT INTO Employee(id, name, salary) VALUES (3, 'Sam', 60000);
INSERT INTO Employee(id, name, salary) VALUES (4, 'Max', 90000);
