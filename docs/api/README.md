# HOLEXA API Reference v1.0.0

## Built-in Functions

| Function | Description | Example |
|----------|-------------|---------|
| `print(x)` | Print to stdout | `print("hello")` |
| `input(msg)` | Read from stdin | `input("Name: ")` |
| `len(x)` | Length of string/list | `len("hello")` |
| `str(x)` | Convert to string | `str(42)` |
| `int(x)` | Convert to int | `int("42")` |
| `float(x)` | Convert to float | `float("3.14")` |
| `type(x)` | Get type name | `type(42)` |
| `range(n)` | Generate range | `range(10)` |
| `append(l,x)` | Add to list | `append(list, 5)` |

## Built-in Types

### Int
```hlx
let x: Int = 42
let y = int("100")
```

### Float
```hlx
let f: Float = 3.14
let g = float("2.71")
```

### String
```hlx
let s: String = "hello"
s.upper()
s.lower()
s.length()
s.contains("ell")
s.replace("l","r")
s.split(",")
s.trim()
s.reverse()
```

### Bool
```hlx
let b: Bool = true
let c = false
```

### List
```hlx
let l = [1, 2, 3]
l.push(4)
l.pop()
l.sort()
l.reverse()
l.length()
l.contains(2)
l.index_of(2)
l.slice(0, 2)
```

### Map
```hlx
let m = {"key": "value"}
m["new"] = "item"
m.keys()
m.values()
m.has("key")
m.delete("key")
```

## Error Types
```hlx
Error("message")
TypeError("type mismatch")
ValueError("invalid value")
IOError("file not found")
NetworkError("connection failed")
```
