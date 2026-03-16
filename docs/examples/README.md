# HOLEXA Examples

## Hello World
```hlx
fn main() {
    print("Hello, World!")
}
```

## Calculator
```hlx
fn add(a: Int, b: Int) -> Int { return a + b }
fn sub(a: Int, b: Int) -> Int { return a - b }
fn mul(a: Int, b: Int) -> Int { return a * b }
fn div(a: Int, b: Int) -> Int {
    if b == 0 { raise Error("Division by zero") }
    return a / b
}

fn main() {
    print(add(10, 5))
    print(sub(10, 5))
    print(mul(10, 5))
    print(div(10, 5))
}
```

## FizzBuzz
```hlx
fn main() {
    for i in 1..101 {
        if i % 15 == 0 {
            print("FizzBuzz")
        } else if i % 3 == 0 {
            print("Fizz")
        } else if i % 5 == 0 {
            print("Buzz")
        } else {
            print(i)
        }
    }
}
```

## Fibonacci
```hlx
fn fib(n: Int) -> Int {
    if n <= 1 { return n }
    return fib(n - 1) + fib(n - 2)
}

fn main() {
    for i in 0..10 {
        print(fib(i))
    }
}
```

## File Read Write
```hlx
import fs

fn main() {
    fs.write("hello.txt", "Hello HOLEXA!")
    let content = fs.read("hello.txt")
    print(content)
}
```

## HTTP Request
```hlx
import http

async fn main() {
    let res = await http.get("https://api.github.com")
    print(res.status)
    print(res.body)
}
```

## Class Example
```hlx
class Person {
    name: String
    age: Int

    fn new(name: String, age: Int) -> Person {
        return Person { name: name, age: age }
    }

    fn greet(self) -> String {
        return "Hi, I am " + self.name
    }

    fn is_adult(self) -> Bool {
        return self.age >= 18
    }
}

fn main() {
    let p = Person.new("Ayush", 20)
    print(p.greet())
    print(p.is_adult())
}
```

## Error Handling
```hlx
fn safe_divide(a: Int, b: Int) -> Int {
    try {
        if b == 0 {
            raise Error("Cannot divide by zero")
        }
        return a / b
    } catch err {
        print("Caught: " + err.message)
        return 0
    }
}

fn main() {
    print(safe_divide(10, 2))
    print(safe_divide(10, 0))
}
```
