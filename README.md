# Eyechecker
![EyeChecker](https://raw.githubusercontent.com/yuchenlichuck/EyeChecker/master/icon.ico)
## What is Eyechecker?
Image segmentation of corneal ulceration using machine learning methods
## Some images of the segmentation of corneal ulceration result.

* The original images

![original](https://github.com/yuchenlichuck/EyeChecker/blob/master/1a.jpg)


* The segmentation result after 7 times `k-means` clustering method with white background. 

![EyeChecker](https://github.com/yuchenlichuck/EyeChecker/blob/master/1a7.jpg)

* The segmentation result after 2 times `k-means` clustering method with black background. 

![EyeChecker](https://github.com/yuchenlichuck/EyeChecker/blob/master/1a221.jpg)

## The introduction of Kmeans clustering methods
* k-means算法中的k代表类簇个数，means代表类簇内数据对象的均值
* k-means算法是一种基于划分的聚类算法，以距离作为数据对象间相似性度量的标准，即数据对象间的距离越小，则它们的相似性越高则它们越有可能在同一个类簇。
* k-means算法以距离作为数据对象间相似性度量的标准，通常采用欧氏距离来计算数据对象间的距离。
* k-means算法聚类过程中，每次迭代，对应的类簇中心需要重新计算（更新）：对应类簇中所有数据对象的均值，即为更新后该类簇的类簇中心。
* k-means算法需要不断地迭代来重新划分类簇，并更新类簇中心，那么迭代终止的条件是什么呢？一般情况，有两种方法来终止迭代：一种方法是设定迭代次数T，当到达第T次迭代，则终止迭代，此时所得类簇即为最终聚类结果；
*   k-means算法思想可描述为：首先初始化K个类簇中心；然后计算各个数据对象到聚类中心的距离，把数据对象划分至距离其最近的聚类中心所在类簇中；
*	接着根据所得类簇，更新类簇中心；然后继续计算各个数据对象到聚类中心的距离，把数据对象划分至距离其最近的聚类中心所在类簇中；
*	接着根据所得类簇，继续更新类簇中心；……一直迭代，直到达到最大迭代次数T，或者两次迭代J的差值小于某一阈值时，迭代终止，得到最终聚类结果。




