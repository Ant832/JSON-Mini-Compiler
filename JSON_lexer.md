## True, False, and Null
Each DFA only recognizes their respective words and no other characters.

![image](images/bools_and_null.png)


## Number
This DFA only recognizes integers, floats, and exponents (all positive or negative) in JSON format.

![image](images/number.png)

## String
This DFA recognizes only JSON formatted strings, except Unicode code points. [SP-~] denotes only the ASCII characters between (ASCII 32) and ~ (126), except for " or \ (which have their own transitions to keep the structure of a DFA).

![image](images/string.png)

## Long String
This DFA recognizes only long strings. [SP-~] denotes only the ASCII characters between (ASCII 32) and ~ (126), except for \ (which has its own transition to keep the structure of a DFA).

![image](images/long_string.png)

## Single Characters
These DFAs simply accept their respective single character input.

![image](images/single_characters.png)


## Whitespace
Accepts only valid whitespaces as inputs.

![image](images/whitespace.png)

## Unknown
May take any character to match input in case of failure of other DFAs.

![image](images/unknown.png)
