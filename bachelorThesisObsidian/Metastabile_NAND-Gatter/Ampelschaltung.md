
### Logiktabelle

| V-Sensor | H-Sensor | > Time | HG   | Übergang |
|----------|----------|--------|------|----------|
| 0        | 0        | 0      | HG'  | No       |
| 0        | 0        | 1      | HG'  | No       |
| 0        | 1        | 0      | HG'  | No       |
| 0        | 1        | 1      | 1    | Maybe    |
| 1        | 0        | 0      | HG'  | No       |
| 1        | 0        | 1      | 0    | Maybe    |
| 1        | 1        | 0      | HG'  | No       |
| 1        | 1        | 1      | -HG' | Yes      |

Realisation mit JK-FF

| V-Sensor | H-Sensor | > Time | J | K |
|----------|----------|--------|---|---|
| 0        | 0        | 0      | 0 | 0 |
| 0        | 0        | 1      | 0 | 0 |
| 0        | 1        | 0      | 0 | 0 |
| 0        | 1        | 1      | 1 | 0 |
| 1        | 0        | 0      | 0 | 0 |
| 1        | 0        | 1      | 0 | 1 |
| 1        | 1        | 0      | 0 | 0 |
| 1        | 1        | 1      | 1 | 1 |


scope_18 HIGH
scope_19 LOW
scope_20 instable 
scope_21 lowest instable
scope_22 highest instable 