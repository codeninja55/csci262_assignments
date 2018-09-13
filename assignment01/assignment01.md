# CSCI262 Systems Security - Assignment 01

Date: 20.08.2018 | Author: Dinh Che (dbac496) | Student ID: 5721970 | Email: dbac496@uowmail.edu.au

## Part One: Short answer questions:

### 1.

$$
N = Tiger(26 \cdot 26 \cdot (10^2) \cdot 1 \cdot (52^2) \cdot (6^3))
$$

$$
Entropy = log_2{N}
$$

$$
\therefore Entropy = log_2{Tiger(26 \cdot 26 \cdot (10^2) \cdot 1 \cdot (52^2) \cdot (6^3))}
$$



### 2.



### 3.

This kind of one-time password system is based on 'what the subject has' and is a form of token-based authentication. An example of this would be a smart card or app with a dynamic password generator as an authenticion protocol. The card or app acts as a token and would generate a unique one-time password (changed periodically, typically 60 seconds) which can be entered into a computer system for authentication.  The card or app token and server must be initialized and kept synchronised. 



### 4.

| Statement                                           | Subjects | Objects                   | Actions               |
| --------------------------------------------------- | -------- | ------------------------- | --------------------- |
| *Alice can climb trees and eat apples.*             | Alice    | Trees and apples          | Climb and eat         |
| *Bob can climb fences, eat apples, and wave flags.* | Bob      | Fences, apples, and flags | Climb, eat, and wave. |
| *Trees can hurt apples.*                            | Trees    | Apples                    | Hurt                  |
| *Carol can jump waves and wave flags.*              | Carol    | Waves and flags           | Jump and wave         |

#### Access Control Matrix

**Action keys:** Climb = C; Eat = E; Wave = W; Hurt = H; Jump = J

| Subjects \ Objects | Apples | Fences | Flags | Trees | Waves |
| -----------------: | :----: | :----: | :---: | :---: | :---: |
|          **Alice** |   E    |        |       |   C   |       |
|            **Bob** |   E    |   C    |   W   |       |       |
|          **Carol** |        |        |   W   |       |   J   |
|          **Trees** |   H    |        |       |       |       |

***

