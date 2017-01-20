C module for Python. Support TTP229 TonTouch. [Datasheet PDF](http://www.robotpark.com/image/data/PRO/91409/TTP229.pdf)

### INSTALL:
```
gcc -shared -o ./libttp229.so `pkg-config --cflags glib-2.0` libttp229.c  `pkg-config --libs glib-2.0` -std=c11 -I/usr/include/python2.7 -lpython2.7
```
```
sudo python setup.py install
```

### USE IN PYTHON:
```python
import libttp229 as sens

class Sensitivity():
    def __init__(self):
        self.isNewData = False
        self.maxKey = 16
        self.keyArray = [0 for x in xrange(self.maxKey)]
    def readData(self):
        index = 0
        data = sens.readData(0x57, 2) + 0b10000000000000000
        for x in bin(data)[3:]:
            self.keyArray[self.maxKey - index] = x
            index += 1
        return self.keyArray
```
