# 在我们执行import时，当前目录是不会变的（就算是执行子目录的文件），还是需要完整的包名
from uncompressor.extract import unzip  # 导入函数unzip, 在其它地方需要调用函数unzip时, 只需要import uncompressor, 然后通过uncompressor.unzip调用
from uncompressor.extract import unrar
from uncompressor.extract import decompression
