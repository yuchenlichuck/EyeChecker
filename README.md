# Eyechecker ( Always Being Improved XD )
![EyeChecker](https://raw.githubusercontent.com/yuchenlichuck/EyeChecker/master/icon.ico)
## What is Eyechecker?
Image segmentation of corneal ulceration using machine learning methods.
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


* k in the k-means algorithm represents the number of clusters, means represents the mean of the data objects in the clusters
* The k-means algorithm is a clustering algorithm based on partitioning. The distance is used as the standard for the similarity index between data objects, that is, the smaller the distance between data objects, the more likely they are replaced by the similarity. Class cluster.
* The k-means algorithm takes distance as the standard of similarity index between data objects, and usually uses Euclidean distance to calculate the distance between data objects.
* During the k-means algorithm clustering process, each time the cluster is repeated, the corresponding cluster center needs to be recalculated (updated): the mean value of all data objects in the corresponding cluster is the cluster center of the updated cluster.
* What is the condition for k-means algorithm to iterate continuously to re-divide clusters, update cluster centers, and then terminate? In general, there are two methods to interrupt inheritance: one method is to set the number of iterations T, and when the Tth iteration is reached, the iteration is terminated, and the class cluster obtained at this time is the final clustering result;
* The idea of k-means algorithm can be described as follows: first initialize the K cluster centers; then calculate the distance between each data object and the cluster center, and divide the data object into the cluster where the nearest cluster center is located;
* Then update the cluster center according to the obtained clusters; then continue to calculate the distance from each data object to the cluster center, and divide the data object into the cluster where the nearest cluster center is located;
* Subsequently, update the cluster center according to the obtained clusters; ... Repeat until the maximum number of iterations T is reached, or when the difference between the two repeated J is less than the minimum threshold, continue to terminate to obtain the final clustering result.

## About Author

> * Li Yuchen
> * Email: liyc@mail.com
> * Majoring in Computer Science and Engineering
> * Junior, Southern University of Science and Technology (SUSTech), Living in Shenzhen
> * Lab Member, Doing Computer Vision & Medical Image Processing Using Deep Learning methods
