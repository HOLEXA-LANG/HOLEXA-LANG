# HOLEXA Language Specification v1.0.0

## Overview
HOLEXA (HLEXA) is a modern, fast, memory-safe programming language.
File extension: .hlx

## Core Philosophy
- Readable like Python
- Fast like C  
- Safe like Rust
- Simple like Go
- Portable everywhere

## Basic Syntax

### Variables
let name = "World"
let age: Int = 25
let pi: Float = 3.14
const MAX = 100

### Functions
fn greet(name: String) -> String {
    return "Hello " + name
}

### Control Flow
if age > 18 {
    print("Adult")
} else {
    print("Minor")
}

### Loops
for i in 0..10 {
    print(i)
}

while x < 10 {
    x = x + 1
}

loop {
    print("running")
}

### Types
Int, Float, Bool, String, List, Map, None

### Error Handling
try {
    result = divide(10, 0)
} catch err {
    print("Error: " + err.message)
}

