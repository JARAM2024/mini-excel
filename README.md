# Mini Excel

[How to Build](#how-to-build)

## Simple Table
![1PNG](images/1.png)

## List commands
![2PNG](images/2.png)

## Parameter

![7PNG](images/7.png)
![8PNG](images/8.png)
![9PNG](images/9.png)

- Point Parameter

Usage: \
(command) point (row_index) (col_index) (set, default value is 0)

- Box Parameter

Usage: \
(command) box (row_index) (col_index) (width) (height) (set, default value is 0)

- List Parameter

Usage: \
(command) list (length) (data1, data2, data3 ...)

## Implement various methods
[Methods to be implemented](./method.h)

![3PNG](images/3.png)

## Hot Compiling
![4PNG](images/4.png)
![5PNG](images/5.png)
![6PNG](images/6.png)

# How to build

## Windows
### Caution
- Hot compiling is not available now.

```console
mkdir build
cd build
cmake ..
./src/mini-excel
```

## MacOS

```bash
mkdir build
cd build
cmake ..
cd ./src
./mini-excel
```
