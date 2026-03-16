# hlxpm — Package Manager Guide v1.0.0

## Installation

hlxpm comes with HOLEXA.
```sh
cp package-manager/hlxpm /usr/local/bin/hlxpm
```

## Commands

| Command | Description |
|---------|-------------|
| `hlxpm install <pkg>` | Install package |
| `hlxpm remove <pkg>` | Remove package |
| `hlxpm list` | List installed |
| `hlxpm search <query>` | Search packages |
| `hlxpm create <name>` | Create project |
| `hlxpm init` | Init package |
| `hlxpm update` | Update all |
| `hlxpm info <pkg>` | Package info |

## Examples
```sh
hlxpm install math
hlxpm install http
hlxpm create myapp
hlxpm list
hlxpm search json
```

## hlxpm.json
```json
{
    "name": "myapp",
    "version": "0.1.0",
    "description": "My HOLEXA app",
    "author": "Your Name",
    "license": "MIT",
    "dependencies": {
        "math": "1.0.0",
        "http": "1.0.0"
    },
    "main": "src/main.hlx"
}
```

## Available Packages

| Package | Description |
|---------|-------------|
| math | Mathematics |
| string | String ops |
| fs | File system |
| http | HTTP client |
| json | JSON parser |
| crypto | Cryptography |
| time | Date/time |
| random | Random gen |
| os | OS access |
| net | Networking |
| io | Input/Output |
| list | List ops |
| map | Map ops |
| process | Processes |
