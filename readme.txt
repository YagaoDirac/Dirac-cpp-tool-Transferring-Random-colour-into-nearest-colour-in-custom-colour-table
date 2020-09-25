This tool has only 1 function now. It converts any colour(colour A) to colour B. Colour A could be any random colour, while colour B is from a user defined colour table. The result colour B is the nearest colour from A. Means this tool converts colour into a colour table according to the distance between the random colour and any colour within the table.

The pseudo code looks like:

question_colour(random_colour)
colour_table(user defined colour table)
distances(question_colour, elements in colour_table)
result_colour = colour_table[min_element(distances)]

In real code, it builds up some new table for a fast query. In fact the code needs 10ish seconds to build up the table, after that, it could be very fast converting.
This tool could help anything which needs converting random colour into a specific set of colours. Gif algo, embroidery, etc.
Also, I have a discord. Reporting, suggestions, chatting are all welcomed.





这个工具的作用是，把任何颜色转换到一个特定的颜色表里面的某种颜色，并且这个任何颜色，和最终的结果颜色，是距离最小的。
好难表达。
这么说嘛
question_colour(random_colour)
colour_table(user defined colour table)
distances(question_colour, elements in colour_table)
result_colour = colour_table[min_element(distances)]

我用了一些方法，做了一个查询表，这个查询表可以非常快速的查找到答案。整个程序大概占用10m左右的内存，制作查询表的时间大概是10秒左右，之后处理图片的时间（按4096x4096分辨率计算）基本在0.1秒左右。非常快。

这个工具是给一位做图形压缩算法研究的朋友写的。具体功能完全按照他的要求来的。如果你们希望在这个工具上加入别的功能，可能来我的discord跟我说，有时间的话也会尽量试试看。

