# HOLEXA Standard Library v1.0.0

## Libraries

| Library | Functions | Description |
|---------|-----------|-------------|
| math | 12 | Mathematics |
| string | 20 | String operations |
| fs | 15 | File system |
| http | 10 | HTTP client/server |
| os | 12 | Operating system |
| json | 8 | JSON parsing |
| time | 10 | Date and time |
| random | 8 | Random generation |
| list | 15 | List operations |
| map | 10 | Map operations |
| crypto | 9 | Cryptography |
| io | 10 | Input/Output |
| net | 10 | Networking |
| process | 7 | Process control |

## Usage
```hlx
import math
import string
import fs

fn main() {
    print(math.PI)
    let name = "holexa"
    print(string.upper(name))
    let exists = fs.exists("file.txt")
    print(exists)
}
```

## math
```hlx
import math

math.abs(-5)
math.sqrt(16)
math.pow(2, 10)
math.max(10, 20)
math.min(10, 20)
math.floor(3.7)
math.ceil(3.2)
math.round(3.5)
math.PI
math.E
```

## string
```hlx
import string

string.upper("hello")
string.lower("HELLO")
string.trim("  hi  ")
string.length("hello")
string.contains("hello", "ell")
string.replace("hello", "l", "r")
string.split("a,b,c", ",")
string.reverse("hello")
string.repeat("ha", 3)
```

## fs
```hlx
import fs

fs.read("file.txt")
fs.write("file.txt", "content")
fs.exists("file.txt")
fs.delete("file.txt")
fs.list_dir("./")
fs.mkdir("newdir")
fs.copy("a.txt", "b.txt")
fs.read_lines("file.txt")
```

## http
```hlx
import http

let res = await http.get("https://api.example.com")
print(res.body)
print(res.status)

let post = await http.post("https://api.example.com", {
    "key": "value"
})
```

## json
```hlx
import json

let obj = json.parse('{"name":"HOLEXA"}')
let str = json.stringify(obj)
let pretty = json.pretty(obj)
```

## time
```hlx
import time

let now = time.now()
time.sleep(1000)
time.format(now, "%Y-%m-%d")
time.add_days(now, 7)
```
