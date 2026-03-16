# HOLEXA Complete Syntax Specification v1.0.0
# Tagline: Code like a Dragon. Think like a Human.

## 1. VARIABLES

let name = "HOLEXA"
let age: Int = 1
let pi: Float = 3.14
let active: Bool = true
const MAX_SIZE = 1000
const APP_NAME = "HOLEXA"

## 2. DATA TYPES

Int       → whole numbers      → 42
Float     → decimal numbers    → 3.14
String    → text               → "hello"
Bool      → true/false         → true
List      → array              → [1, 2, 3]
Map       → key-value          → {"key": "value"}
None      → empty/null         → none
Byte      → raw byte           → 0xFF
Any       → any type           → any value

## 3. FUNCTIONS

fn greet(name: String) -> String {
    return "Hello " + name
}

fn add(a: Int, b: Int) -> Int {
    return a + b
}

fn main() {
    print(greet("World"))
}

## 4. CONTROL FLOW

### If
if age > 18 {
    print("Adult")
}

### If Else
if age > 18 {
    print("Adult")
} else {
    print("Minor")
}

### If Else If
if score > 90 {
    print("A")
} else if score > 80 {
    print("B")
} else if score > 70 {
    print("C")
} else {
    print("Fail")
}

## 5. LOOPS

### For Loop
for i in 0..10 {
    print(i)
}

### While Loop
while x < 10 {
    x = x + 1
}

### Infinite Loop
loop {
    print("running")
    break
}

### Iterator Loop
for item in list {
    print(item)
}

## 6. CLASSES

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

let dog = Animal.new("Rex", 5)
print(dog.speak())

## 7. ERROR HANDLING

try {
    let result = divide(10, 0)
    print(result)
} catch err {
    print("Error: " + err.message)
} finally {
    print("Done")
}

fn divide(a: Int, b: Int) -> Int {
    if b == 0 {
        raise Error("Cannot divide by zero")
    }
    return a / b
}

## 8. IMPORTS AND MODULES

import math
import fs
import http
import "mymodule"
from math import sqrt, pi
from http import get, post

## 9. ASYNC PROGRAMMING

async fn fetchData(url: String) -> String {
    let response = await http.get(url)
    return response.body
}

async fn main() {
    let data = await fetchData("https://api.example.com")
    print(data)
}

## 10. GENERICS

fn largest<T>(list: List<T>) -> T {
    let biggest = list[0]
    for item in list {
        if item > biggest {
            biggest = item
        }
    }
    return biggest
}

## 11. TRAITS AND INTERFACES

trait Printable {
    fn print(self) -> None
    fn toString(self) -> String
}

class Dog implements Printable {
    name: String

    fn print(self) -> None {
        print("Dog: " + self.name)
    }

    fn toString(self) -> String {
        return "Dog(" + self.name + ")"
    }
}

## 12. MEMORY AND SAFETY RULES

- No null pointer dereference
- No buffer overflow
- No use after free
- No data races
- Automatic memory management
- Optional manual memory control

## 13. CONCURRENCY

spawn fn worker(id: Int) {
    print("Worker " + id + " running")
}

spawn worker(1)
spawn worker(2)
spawn worker(3)

channel<Int> ch = Channel.new()
ch.send(42)
let val = ch.receive()

## 14. PYTHON INTEROP

python {
    import numpy as np
    arr = np.array([1, 2, 3])
    result = arr.sum()
}
print(result)

## 15. JAVASCRIPT INTEROP

js {
    const x = document.getElementById("app")
    x.innerHTML = "Hello from HOLEXA"
}

## 16. C INTEROP

extern fn printf(fmt: String, ...) -> Int

## 17. COMMENTS

// Single line comment

/*
Multi line
comment
*/

## 18. STRING OPERATIONS

let s = "Hello World"
let upper = s.upper()
let lower = s.lower()
let len = s.length()
let sub = s.slice(0, 5)
let has = s.contains("World")
let replaced = s.replace("World", "HOLEXA")
let parts = s.split(" ")

## 19. LIST OPERATIONS

let nums = [1, 2, 3, 4, 5]
nums.push(6)
nums.pop()
let first = nums[0]
let sliced = nums.slice(1, 3)
let sorted = nums.sort()
let mapped = nums.map(fn(x) { return x * 2 })
let filtered = nums.filter(fn(x) { return x > 2 })

## 20. MAP OPERATIONS

let person = {
    "name": "HOLEXA",
    "version": "1.0.0",
    "fast": true
}
person["author"] = "You"
let keys = person.keys()
let vals = person.values()
let has_key = person.has("name")

## 21. FILE SYSTEM

import fs

let content = fs.read("file.txt")
fs.write("output.txt", "Hello HOLEXA")
fs.append("log.txt", "new line")
let exists = fs.exists("file.txt")
fs.delete("old.txt")
let files = fs.list("./")

## 22. HTTP REQUESTS

import http

let res = await http.get("https://api.example.com/data")
print(res.status)
print(res.body)

let post_res = await http.post("https://api.example.com/create", {
    "name": "test",
    "value": 42
})

## 23. OPERATORS

Arithmetic:   +  -  *  /  %  **
Comparison:   ==  !=  >  <  >=  <=
Logical:      and  or  not
Bitwise:      &  |  ^  ~  <<  >>
Assignment:   =  +=  -=  *=  /=

## 24. LAMBDA FUNCTIONS

let double = fn(x: Int) -> Int { return x * 2 }
let result = double(5)

let nums = [1, 2, 3, 4, 5]
let doubled = nums.map(fn(x) { return x * 2 })

## 25. PATTERN MATCHING

match value {
    1 => print("one")
    2 => print("two")
    3..10 => print("three to ten")
    _ => print("other")
}

