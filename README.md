Implementation of different algorithms

antisym.cpp

	Count the number of antisymetric subgstrings of given string over the alphabet {0,1} in O(length) time using Manacher algorithm.

dft.cpp

	Fast fourier transformation in finite field

range.cpp

	2d range queries in cartesian plane.

	operations:

		add point in O(log(y)log(points))
	
		delete point in O(log(y)log(points))
	
		2d query in O(log(y)log(points))
	
		memory complexity: O(points*log(y))

kquery.cpp

	Data structure extenging array with operation:

		query(b,e,k): find the number of elements <=k in the subarray [b..e] in time  O(sqrt(n)log(n))
	
		val(index,v): change the value of array[index] to v in time O(sqrt(n))

	


