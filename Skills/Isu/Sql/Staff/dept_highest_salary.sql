-- https://leetcode.com/problems/department-highest-salary/
DROP TABLE IF EXISTS Employee;
CREATE TABLE Employee(
    Id INT,
    Name VARCHAR,
    Salary INT,
    DepartmentId INT
);

DROP TABLE IF EXISTS Department;
CREATE TABLE Department(
    Id Int,
    Name VARCHAR
);

INSERT INTO Employee(Id, Name, Salary, DepartmentId) VALUES(1, 'Joe', 70000, 1);
INSERT INTO Employee(Id, Name, Salary, DepartmentId) VALUES(2, 'Jim', 90000, 1);
INSERT INTO Employee(Id, Name, Salary, DepartmentId) VALUES(3, 'Henry', 80000, 2);
INSERT INTO Employee(Id, Name, Salary, DepartmentId) VALUES(4, 'Sam', 60000, 2);
INSERT INTO Employee(Id, Name, Salary, DepartmentId) VALUES(5, 'Max', 90000, 1);

INSERT INTO Department(Id, Name) VALUES (1, 'IT');
INSERT INTO Department(Id, Name) VALUES (2, 'Sales');
