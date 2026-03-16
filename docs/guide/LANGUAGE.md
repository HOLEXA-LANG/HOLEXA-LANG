# HOLEXA Language Guide v1.0.0

> Code like a Dragon. Think like a Human.

---

## 1. Introduction

HOLEXA is a modern, fast, memory-safe programming language.

- Fast like C
- Safe like Rust
- Readable like Python
- Simple like Go

File extension: `.hlx`

---

## 2. Hello World
```hlx
fn main() {
    print("Hello, World!")
}
```

Run:
```sh
hlxc run hello.hlx
```

---

## 3. Variables
```hlx
let name = "HOLEXA"
let age: Int = 1
let pi: Float = 3.14
let active: Bool = true
const MAX = 1000
const APP = "HOLEXA"
```

### Types

| Type | Example | Description |
|------|---------|-------------|
| Int | 42 | Whole number |
| Float | 3.14 | Decimal number |
| String | "hello" | Text |
| Bool | true | True or false |
| List | [1,2,3] | Array |
| Map | {"k":"v"} | Key-value |
| None | none | Empty value |

---

## 4. Functions
```hlx
fn greet(name: String) -> String {
    return "Hello " + name
}

fn add(a: Int, b: Int) -> Int {
    return a + b
}

fn main() {
    print(greet("Dragon"))
    print(add(10, 20))
}
```

---

## 5. Control Flow

### If / Else
```hlx
let age = 20

if age > 18 {
    print("Adult")
} else if age == 18 {
    print("Just 18")
} else {
    print("Minor")
}
```

### Match
```hlx
match score {
    100 => print("Perfect")
    90  => print("Excellent")
    _   => print("Keep trying")
}
```

---

## 6. Loops

### For Loop
```hlx
for i in 0..10 {
    print(i)
}
```

### While Loop
```hlx
let x = 0
while x < 10 {
    print(x)
    x = x + 1
}
```

### Infinite Loop
```hlx
loop {
    print("running")
    break
}
```

### Iterator
```hlx
let fruits = ["apple", "banana", "mango"]
for fruit in fruits {
    print(fruit)
}
```

---

## 7. Classes
```hlx
class Animal {
    name: String
    age: Int

    fn new(name: String, age: Int) -> Animal {
        return Animal { name: name, age: age }
    }

    fn speak(self) -> String {
        return self.name + " says hello!"
    }
}

fn main() {
    let dog = Animal.new("Rex", 5)
    print(dog.speak())
}
```

---

## 8. Error Handling
```hlx
fn divide(a: Int, b: Int) -> Int {
    if b == 0 {
        raise Error("Division by zero")
    }
    return a / b
}

fn main() {
    try {
        let result = divide(10, 0)
        print(result)
    } catch err {
        print("Error: " + err.message)
    } finally {
        print("Done")
    }
}
```

---

## 9. Async Programming
```hlx
async fn fetch(url: String) -> String {
    let res = await http.get(url)
    return res.body
}

async fn main() {
    let data = await fetch("https://api.example.com")
    print(data)
}
```

---

## 10. Imports
```hlx
import math
import fs
import http
from math import sqrt, PI
from http import get, post
```

---

## 11. Generics
```hlx
fn largest<T>(list: List<T>) -> T {
    let max = list[0]
    for item in list {
        if item > max {
            max = item
        }
    }
    return max
}
```

---

## 12. Concurrency
```hlx
spawn fn worker(id: Int) {
    print("Worker " + id + " running")
}

fn main() {
    spawn worker(1)
    spawn worker(2)
    spawn worker(3)
}
```

---

## 13. Operators
```
Arithmetic:   +  -  *  /  %  **
Comparison:   ==  !=  >  <  >=  <=
Logical:      and  or  not
Assignment:   =  +=  -=  *=  /=
```

---

## 14. Comments
```hlx
// Single line comment

/*
Multi line
comment
*/
```

---

## 15. String Operations
```hlx
let s = "Hello HOLEXA"
print(s.upper())
print(s.lower())
print(s.length())
print(s.contains("HOLEXA"))
print(s.replace("HOLEXA", "World"))
print(s.split(" "))
```

---

## 16. List Operations
```hlx
let nums = [1, 2, 3, 4, 5]
nums.push(6)
nums.pop()
let sorted = nums.sort()
let mapped = nums.map(fn(x) { return x * 2 })
let filtered = nums.filter(fn(x) { return x > 2 })
```

---

## 17. Map Operations
```hlx
let person = {
    "name": "HOLEXA",
    "age": 1
}
person["version"] = "1.0.0"
let keys = person.keys()
let vals = person.values()
```

---

## 18. Python Interop
```hlx
python {
    import numpy as np
    result = np.array([1,2,3]).sum()
}
print(result)
```

---

## 19. JavaScript Interop
```hlx
js {
    const el = document.getElementById("app")
    el.innerHTML = "Hello HOLEXA"
}
```

---

## 20. C Interop
```hlx
extern fn printf(fmt: String, ...) -> Int

fn main() {
    printf("Hello from C!")
}
```
