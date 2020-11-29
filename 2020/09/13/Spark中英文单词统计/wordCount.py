from pyspark import SparkConf, SparkContext
import jieba

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)
# read file
filePath = '/home/x/IdeaProjects/Learning_CS/Spark-learning/src/main/resource/yuliaoFile/盗墓笔记全集'
textRDD = sc.textFile(filePath)
# 分词,组成{word:1
splitRDD = textRDD.flatMap(lambda line: jieba.lcut(line))
# word 
wordRdd = splitRDD.map(lambda word: (word ,1)).reduceByKey(lambda a, b: a + b)
wordRddSortByCount = wordRdd.sortBy(lambda a: a[1])
wordRddSortByCount.saveAsTextFile("./"+filePath.split('/')[-1]+"sortedResult")
wordRdd.saveAsTextFile("./"+filePath.split('/')[-1]+"result")
