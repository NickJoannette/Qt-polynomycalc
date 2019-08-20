# polynomial calculator & plotter

![ui](https://raw.githubusercontent.com/NickJoannette/qt-poly-calc/master/polycalc.PNG?token=AK7AUQTA66LB4KDEJEOA3H25LQORK)

This is a simple program I worked on to introduce myself to qt, c++ design for desktop applications, and handling user input signals.

The legal characters for polynomial entry are, in this order: +/-, digits, decimal point, digits (if necessary), x, ^, digits.
### Legal Input
Spaces anywhere are ignored.
Examples:
```
0x^0 
+4.x^2
-  5.054x^18
+0004x^1
```
negative exponents not currently accepted


### Error Handling

![error handling](https://raw.githubusercontent.com/NickJoannette/qt-poly-calc/master/mayimp.PNG)

### Work to do
Have to add in dynamic axis resizing dependent on user input and renovate the parsing handler.
