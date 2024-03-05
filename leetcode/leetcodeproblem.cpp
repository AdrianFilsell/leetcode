
#include "pch.h"
#include "leetcodeproblem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString leetcodeproblem1799::getdifficulty(void)const
{
	CString cs;
	cs += CString("hard");
	return cs;
}

CString leetcodeproblem1799::gettitle(void)const
{
	CString cs;
	cs += _T("1799");
	return cs;
}

CString leetcodeproblem1799::getsubmissions(void)const
{
	CString cs;
	cs += _T("100.3K");
	return cs;
}

CString leetcodeproblem1799::getacceptancerate(void)const
{
	CString cs;
	cs += _T("58.2%");
	return cs;
}

CString leetcodeproblem1799::getruntimerank(void)const
{
	CString cs;
	cs += _T("top 9.17%");
	return cs;
}

CString leetcodeproblem1799::getmemoryrank(void)const
{
	CString cs;
	cs += _T("top 6.25%");
	return cs;
}

CString leetcodeproblem1799::getdescription(void)const
{
	CString cs;
	cs += _T("leetcode1799:Maximize Score After N Operations\r\n");
	cs += _T("\r\n");
	cs += _T("You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.\r\n");
	cs += _T("\r\n");
	cs += _T("In the ith operation (1-indexed), you will:\r\n");
	cs += _T("\r\n");
	cs += _T("Choose two elements, x and y.\r\n");
	cs += _T("Receive a score of i * gcd(x, y).\r\n");
	cs += _T("Remove x and y from nums.\r\n");
	cs += _T("Return the maximum score you can receive after performing n operations.\r\n");
	cs += _T("\r\n");
	cs += _T("The function gcd(x, y) is the greatest common divisor of x and y.\r\n");
	cs += _T("\r\n");
	cs += _T("Constraints:\r\n");
	cs += _T("\r\n");
	cs += _T("1 <= n <= 7\r\n");
	cs += _T("nums.length == 2 * n\r\n");
	cs += _T("1 <= nums[i] <= 106");
	
	return cs;
}

CString leetcodeproblem1799::getexamplesdescription(void)const
{
	CString cs;
	cs += _T("Example 1:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: {1,2}\r\n");
	cs += _T("Output: 1\r\n");
	cs += _T("Explanation: (1 * gcd(1, 2)) = 1\r\n");
	
	cs += _T("\r\n");
	cs += _T("Example 2:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: {3,4,6,8}\r\n");
	cs += _T("Output: 11\r\n");
	cs += _T("Explanation: (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11\r\n");

	cs += _T("\r\n");
	cs += _T("Example 3:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: {1,2,3,4,5,6}\r\n");
	cs += _T("Output: 11\r\n");
	cs += _T("Explanation: (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14");

	return cs;
}

CString leetcodeproblem1799::getrundescription(void)const
{
	std::vector<std::vector<int>> v = {
											{1,2,3,4,5,6},
											{3,4,6,8},
											{1,2},
											{415,230,471,705,902,87},
											{5987,402328,821723,898577,860342,929227,984046,776475},
											{9,17,16,15,18,13,18,20},
											{773274,313112,131789,222437,918065,49745,321270,74163,900218,80160,325440,961730},
											{39759,619273,859218,228161,944571,597983,483239,179849,868130,909935,912143,817908,738222,653224}
									  };

	Solution sl;
	CString cs;
	auto i = v.cbegin(),end=v.cend();
	for(;i!=end;++i)
	{
		if(std::distance(v.cbegin(),i))
			cs += _T("\r\n\r\n");
					
		std::vector<int> nums=*i;
		auto r = sl.maxScore(nums);
		CString csL;
		csL.Format(_T("Example %li:\r\n\r\nInput: %s\r\nOutput: %li"),std::distance(v.cbegin(),i)+1,getszformat(*i),r);
		cs += csL;
	}
	return cs;
}

CString leetcodeproblem1799::getreasoningdescription(void)const
{
	// NOTES
	// 
	// gcd is an expensive calculation so lets precalculate all possible pairs and place in a 2d lookup table
	// i.e nums {2,4,6,8}, diagonal not required
	//		2	4	6	8
	//	2	X	2	2	2
	//	4	2	X	2	4
	//	6	2	2	X	2
	//	8	2	4	2	X

	// use recursion to exhaustively try every permutation i.e.
	
	// PSUEDO CODE
	// 
	// loop I [0,nums.length)
	//		loop J [I+1,nums.length)
	//			if( lookup table value (I,J) + recurse ( with I and J erased from nums ) > max ) - integrate op count multiplier
	//				max = local

	// SPEED UPS
	// 
	// speedups:
	//		dont create a local nums vector with I and J erased instead always pass nums with a bitarray indicating which indices have been erased and should be avoided
	//		max 14 ints in nums so 16 bit int would be fine to represent indices mask

	//		dont repeat attempts by using a cache of previously calculated max values for a given set of nums at a given point in the search ( point in search comes from op multiplier value )
	//		op_multilier range [1,7], indices range [0,(2^14)-1], cache needs to hold 'max' gcd value for all (2^14)-1 possibilities at all '7' levels i.e. 114,681
	//		the idea of checking 'if we have been here before' - https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/

	CString cs;

	cs += _T("\r\n---------- notes\r\n");

	cs += _T("\r\ngcd is an expensive calculation so lets precalculate all possible pairs and place in a 2d lookup table\r\n");
	cs += _T("i.e nums {2,4,6,8}, diagonal not required\r\n");
	cs += _T("\t\t2\t4\t6\t8\r\n");
	cs += _T("\t2\tX\t2\t2\t2\r\n");
	cs += _T("\t4\t2\tX\t2\t4\r\n");
	cs += _T("\t6\t2\t2\tX\t2\r\n");
	cs += _T("\t8\t2\t4\t2\tX\r\n");

	cs += _T("\r\nuse recursion to exhaustively try every permutation i.e.\r\n");

	cs += _T("\r\n---------- psuedo code\r\n");

	cs += _T("\r\nloop I [0,nums.length)\r\n");
	cs += _T("\tloop J [I+1,nums.length)\r\n");
	cs += _T("\t\tif( lookup table value (I,J) + recurse ( with I and J erased from nums ) > max ) - integrate op count multiplier\r\n");
	cs += _T("\t\t\tmax = local\r\n");
	
	cs += _T("\r\n---------- speedups\r\n");

	cs += _T("\r\ndont create a local nums vector with I and J erased instead always pass nums with a bitarray indicating which indices have been erased and should be avoided\r\n");
	cs += _T("max 14 ints in nums so 16 bit int would be fine to represent indices mask\r\n");

	cs += _T("\r\ndont repeat attempts by using a cache of previously calculated max values for a given set of nums at a given point in the search ( point in search comes from op multiplier value )\r\n");
	cs += _T("op_multilier range [1,7], indices range [0,(2^14)-1], cache needs to hold 'max' gcd value for all (2^14)-1 possibilities at all '7' levels i.e. 114,681\r\n");
	cs += _T("the idea of checking 'if we have been here before' - https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/");

	return cs;
}

CString leetcodeproblem1807::gettitle(void)const
{
	CString cs;
	cs += CString("1807");
	return cs;
}

CString leetcodeproblem1807::getdifficulty(void)const
{
	CString cs;
	cs += CString("medium");
	return cs;
}

CString leetcodeproblem1807::getsubmissions(void)const
{
	CString cs;
	cs += _T("43.4K");
	return cs;
}

CString leetcodeproblem1807::getacceptancerate(void)const
{
	CString cs;
	cs += _T("66.7%");
	return cs;
}

CString leetcodeproblem1807::getruntimerank(void)const
{
	CString cs;
	cs += _T("top 83.94%");
	return cs;
}

CString leetcodeproblem1807::getmemoryrank(void)const
{
	CString cs;
	cs += _T("top 1.9%");
	return cs;
}

CString leetcodeproblem1807::getdescription(void)const
{
	CString cs;
	cs += _T("leetcode1807:Evaluate the Bracket Pairs of a String\r\n");
	cs += _T("\r\n");
	cs += _T("You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.\r\n");
	cs += _T("\r\n");
	cs += _T("For example, in the string \"(name)is(age)yearsold\", there are two bracket pairs that contain the keys \"name\" and \"age\".\r\n");
	cs += _T("You know the values of a wide range of keys. This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.\r\n");
	cs += _T("\r\n");
	cs += _T("You are tasked to evaluate all of the bracket pairs. When you evaluate a bracket pair that contains some key keyi, you will:\r\n");
	cs += _T("\r\n");
	cs += _T("Replace keyi and the bracket pair with the key's corresponding valuei.\r\n");
	cs += _T("If you do not know the value of the key, you will replace keyi and the bracket pair with a question mark \"?\" (without the quotation marks).\r\n");
	cs += _T("Each key will appear at most once in your knowledge. There will not be any nested brackets in s.\r\n");
	cs += _T("\r\n");
	cs += _T("Return the resulting string after evaluating all of the bracket pairs.");

	return cs;
}

CString leetcodeproblem1807::getexamplesdescription(void)const
{
	CString cs;
	cs += _T("Example 1:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: s = \"(name)is(age)yearsold\", knowledge = [[\"name\",\"bob\"],[\"age\",\"two\"]]\r\n");
	cs += _T("Output: \"bobistwoyearsold\"\r\n");
	cs += _T("Explanation:\r\n");
	cs += _T("The key \"name\" has a value of \"bob\", so replace \"(name)\" with \"bob\".\r\n");
	cs += _T("The key \"age\" has a value of \"two\", so replace \"(age)\" with \"two\".\r\n");
	
	cs += _T("\r\n");
	cs += _T("Example 2:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: s = \"hi(name)\", knowledge = [[\"a\",\"b\"]]\r\n");
	cs += _T("Output: \"hi?\"\r\n");
	cs += _T("Explanation: As you do not know the value of the key \"name\", replace \"(name)\" with \"?\".\r\n");

	cs += _T("\r\n");
	cs += _T("Example 3:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: s = \"(a)(a)(a)aaa\", knowledge = [[\"a\",\"yes\"]]\r\n");
	cs += _T("Output: \"yesyesyesaaa\"\r\n");
	cs += _T("Explanation:\r\n");
	cs += _T("The same key can appear multiple times.\r\n");
	cs += _T("The key \"a\" has a value of \"yes\", so replace all occurrences of \"(a)\" with \"yes\".\r\n");
	cs += _T("Notice that the \"a\"s not in a bracket pair are not evaluated.");

	return cs;
}

CString leetcodeproblem1807::getrundescription(void)const
{
	std::vector<std::vector<std::vector<std::string>>> vK = {
											{std::vector<std::string>{"name","bob"},std::vector<std::string>{"age","two"}},
											{std::vector<std::string>{"a","b"}},
											{std::vector<std::string>{"a","yes"}}
									  };
	std::vector<std::string> vS = {
											{"(name)is(age)yearsold"},
											{"hi(name)"},
											{"(a)(a)(a)aaa"}
									  };

	Solution sl;
	CString cs;
	auto i = vK.cbegin(),end=vK.cend();
	auto j = vS.cbegin();
	for(;i!=end;++i,++j)
	{
		if(std::distance(vK.cbegin(),i))
			cs += _T("\r\n\r\n");
					
		std::vector<std::vector<std::string>> k=*i;
		const std::string s=*j;
		const std::string r = sl.evaluate(s,k);
		CString csL;
		csL.Format(_T("Example %li:\r\n\r\nInput: s = %s, knowledge = %s\r\nOutput: %s"),std::distance(vK.cbegin(),i)+1,CString(CStringA(s.c_str())),getszformat(*i),CString(CStringA(r.c_str())));
		cs += csL;
	}
	return cs;
}

CString leetcodeproblem1807::getreasoningdescription(void)const
{
	// NOTES
	// 
	// build up a string from input string sections deliminated by input begin/input end/dictionary key i.e.
	
	// PSUEDO CODE
	// 
	// sort input dictionary
	// loop next (KEY) available
	//		append string from prev (KEY) to (KEY)
	//		if KEY valid
	//			append VALUE
	//		else
	//			append "?"
	// append remaining
	
	CString cs;

	cs += _T("\r\n---------- notes\r\n");

	cs += _T("\r\nbuild up a string from input string sections deliminated by input begin/input end/dictionary key i.e.\r\n");

	cs += _T("\r\n---------- psuedo code\r\n");

	cs += _T("\r\nsort input dictionary\r\n");
	cs += _T("loop next (KEY) available\r\n");
	cs += _T("\tappend string from prev (KEY) to (KEY)\r\n");
	cs += _T("\tif (KEY) valid\r\n"); 
	cs += _T("\t\tappend VALUE\r\n");
	cs += _T("\telse\r\n");
	cs += _T("\t\tappend \"?\"\r\n");
	cs += _T("append remaining");

	return cs;
}

CString leetcodeproblem1793::gettitle(void)const
{
	CString cs;
	cs += CString("1793");
	return cs;
}

CString leetcodeproblem1793::getdifficulty(void)const
{
	CString cs;
	cs += CString("hard");
	return cs;
}

CString leetcodeproblem1793::getsubmissions(void)const
{
	CString cs;
	cs += _T("109.5K");
	return cs;
}

CString leetcodeproblem1793::getacceptancerate(void)const
{
	CString cs;
	cs += _T("64.5%");
	return cs;
}

CString leetcodeproblem1793::getruntimerank(void)const
{
	CString cs;
	cs += _T("top 36.17%");
	return cs;
}

CString leetcodeproblem1793::getmemoryrank(void)const
{
	CString cs;
	cs += _T("top 9.52%");
	return cs;
}

CString leetcodeproblem1793::getdescription(void)const
{
	CString cs;
	cs += _T("leetcode1793:Maximum Score of a Good Subarray\r\n");
	cs += _T("\r\n");
	cs += _T("You are given an array of integers nums (0-indexed) and an integer k.\r\n");
	cs += _T("\r\n");
	cs += _T("The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1).\r\n");
	cs += _T("\r\n");
	cs += _T("A good subarray is a subarray where i <= k <= j.\r\n");
	cs += _T("\r\n");
	cs += _T("Return the maximum possible score of a good subarray.");
	cs += _T("\r\n");
	cs += _T("Constraints:\r\n");
	cs += _T("\r\n");
	cs += _T("1 <= nums.length <= 10^5\r\n");
	cs += _T("1 <= nums[i] <= 2 * 10^4\r\n");
	cs += _T("0 <= k < nums.length");

	return cs;
}

CString leetcodeproblem1793::getexamplesdescription(void)const
{
	CString cs;
	cs += _T("Example 1:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: nums = [1,4,3,7,4,5], k = 3\r\n");
	cs += _T("Output: 15\r\n");
	cs += _T("Explanation:\r\n");
	cs += _T("The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15.\r\n");
	
	cs += _T("\r\n");
	cs += _T("Example 2:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: nums = [5,5,4,5,4,1,1,1], k = 0\r\n");
	cs += _T("Output: 20\r\n");
	cs += _T("Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) * (4-0+1) = 4 * 5 = 20.");
	
	return cs;
}

CString leetcodeproblem1793::getrundescription(void)const
{
	std::vector<std::vector<int>> vNums = {
											{1,4,3,7,4,5},
											{5,5,4,5,4,1,1,1}
										  };
	std::vector<int> vK = {3,0};

	Solution sl;
	CString cs;
	auto i = vNums.cbegin(),end=vNums.cend();
	auto j = vK.cbegin();
	for(;i!=end;++i,++j)
	{
		if(std::distance(vNums.cbegin(),i))
			cs += _T("\r\n\r\n");
					
		std::vector<int> nums=*i;
		const int k=*j;
		const int n=sl.maximumScore(nums,k);
		CString csL;
		csL.Format(_T("Example %li:\r\n\r\nInput: nums = %s, k = %li\r\nOutput: %li"),std::distance(vNums.cbegin(),i)+1,getszformat(nums),k,n);
		cs += csL;
	}
	return cs;
}

CString leetcodeproblem1793::getreasoningdescription(void)const
{
	// NOTES
	// 
	// "A good subarray is a subarray where i <= k <= j." should really read
	// "A valid subarray is a subarray where i <= k <= j."

	// think of the supplied 'k' vector index as a 'pivot' point, initialise 'i' and 'j' to 'k',
	// widen the search range [i,j] by decrementing 'i' and incrementing 'j' in order to find the largest range with the largest 'min' value
	
	// PSUEDO CODE
	// 
	// loop i>0 AND j<nums.length-1
	//		if nums[i-1] < nums[j+1] ( we want the largest value multiplied by the range size )
	//			extend range in the j direction
	//		else
	//			extend range in the i direction 
	//		evalute max
	// loop [0,i)
	//		evalute max
	// loop [j+1,nums.length)
	//		evalute max
	
	CString cs;

	cs += _T("\r\n---------- notes\r\n");

	cs += _T("\r\n\"A good subarray is a subarray where i <= k <= j.\"... should really read\r\n");
	cs += _T("\"A valid subarray is a subarray where i <= k <= j.\"...\r\n");

	cs += _T("\r\nthink of the supplied 'k' vector index as a 'pivot' point, initialise 'i' and 'j' to 'k',\r\n");
	cs += _T("widen the search range [i,j] by decrementing 'i' and incrementing 'j' in order to find the largest range with the largest 'min' value\r\n");

	cs += _T("\r\n---------- psuedo code\r\n");

	cs += _T("\r\nloop i>0 AND j<nums.length-1\r\n");
	cs += _T("\tif nums[i-1] < nums[j+1] ( we want the largest value multiplied by the range size )\r\n");
	cs += _T("\t\textend range in the j direction\r\n");
	cs += _T("\telse\r\n");
	cs += _T("\t\textend range in the i direction\r\n");
	cs += _T("\tevalute max\r\n");
	cs += _T("loop [0,i)\r\n");
	cs += _T("\tevalute max\r\n");
	cs += _T("loop [j+1,nums.length)\r\n");
	cs += _T("\tevalute max");
	
	return cs;
}

CString leetcodeproblem84::gettitle(void)const
{
	CString cs;
	cs += CString("84");
	return cs;
}

CString leetcodeproblem84::getdifficulty(void)const
{
	CString cs;
	cs += CString("hard");
	return cs;
}

CString leetcodeproblem84::getsubmissions(void)const
{
	CString cs;
	cs += _T("1.9M");
	return cs;
}

CString leetcodeproblem84::getacceptancerate(void)const
{
	CString cs;
	cs += _T("44.0%");
	return cs;
}

CString leetcodeproblem84::getruntimerank(void)const
{
	CString cs;
	cs += _T("???");
	return cs;
}

CString leetcodeproblem84::getmemoryrank(void)const
{
	CString cs;
	cs += _T("top 0.03%");
	return cs;
}

CString leetcodeproblem84::getdescription(void)const
{
	CString cs;
	cs += _T("leetcode84:Largest Rectangle in Histogram\r\n");
	cs += _T("\r\n");
	cs += _T("Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.\r\n");
	cs += _T("\r\n");
	cs += _T("Constraints:\r\n");
	cs += _T("\r\n");
	cs += _T("1 <= heights.length <= 10^5\r\n");
	cs += _T("0 <= heights[i] <= 10^4");

	return cs;
}

CString leetcodeproblem84::getexamplesdescription(void)const
{
	CString cs;
	cs += _T("Example 1:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: heights = {2,1,5,6,2,3}\r\n");
	cs += _T("Output: 10\r\n");
	cs += _T("Explanation:\r\n");
	cs += _T("The above is a histogram where width of each bar is 1.\r\n");
	cs += _T("The largest rectangle is 2 * 5 = 10 units.\r\n");
	
	cs += _T("\r\n");
	cs += _T("Example 2:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: heights = {2,4}\r\n");
	cs += _T("Output: 4\r\n");
	cs += _T("The above is a histogram where width of each bar is 1.\r\n");
	cs += _T("The largest rectangle is 2 * 2 = 4 units.");
	
	return cs;
}

CString leetcodeproblem84::getrundescription(void)const
{
	std::vector<std::vector<int>> vNums = {
											{2,2,2},
											{2,1,2},
											{2,1,5,6,2,3},
											{2,4},
											{6,1,9,8,6,6,0,5,9,0,8,8,6,6,6,2,7,9,4}
										  };

	Solution sl;
	CString cs;
	auto i = vNums.cbegin(),end=vNums.cend();
	for(;i!=end;++i)
	{
		if(std::distance(vNums.cbegin(),i))
			cs += _T("\r\n\r\n");
					
		std::vector<int> nums=*i;
		const int n=sl.largestRectangleArea(nums);
		CString csL;
		csL.Format(_T("Example %li:\r\n\r\nInput: nums = %s\r\nOutput: %li"),std::distance(vNums.cbegin(),i)+1,getszformat(nums),n);
		cs += csL;
	}
	return cs;
}

CString leetcodeproblem84::getreasoningdescription(void)const
{
	// NOTES
	// 
	// Maintain a column of rect widths i.e. imagine a histogram with 3 columns {1,3,4}
	// iterating from right to left the column of rect widths would become:
	// | 1 |          | 1 |          | 1 |
	// | 1 |    ->    | 2 |    ->    | 2 |
	// | 1 |          | 2 |          | 2 |
	// | 1 |          | 2 |          | 3 |
	// maintaining a column of rect widths allows us to evaluate rect areas at any time i.e.
	// | 1 |
	// | 2 |
	// | 2 |
	// | 3 |
	// describes (w x h) rect areas: (1 x 4), (2 x 3), (2 x 2), (3 x 1)
	
	// PSUEDO CODE
	// 
	// loop (columns,0]
	//		if column height greater than prev column height
	//			increment counts for heights [0,prev column height)
	//			set counts for heights [prev column height, column height) to 1
	//		else
	//			increment counts for heights [0,column height - 1]
	//			evalute max rects [column height,prev column height - 1]
	//	evalute max rects [0,first column height - 1]
	
	// SPEED UPS
	// 
	// speedup:
	//		look for a run of equal height columns as if we maintain run length and column height no need to increment counts

	CString cs;

	cs += _T("\r\n---------- notes\r\n");

	cs += _T("\r\nMaintain a column of rect widths i.e. imagine a histogram with 3 columns {1,3,4}\r\n");
	cs += _T("iterating from right to left the column of rect widths would become:\r\n");
	cs += _T("| 1 |\t\t| 1 |\t\t| 1 |\r\n");
	cs += _T("| 1 |\t->\t| 2 |\t->\t| 2 |\r\n");
	cs += _T("| 1 |\t\t| 2 |\t\t| 2 |\r\n");
	cs += _T("| 1 |\t\t| 2 |\t\t| 3 |\r\n");
	cs += _T("maintaining a column of rect widths allows us to evaluate rect areas at any time i.e.\r\n");
	cs += _T("| 1 |\r\n| 2 |\r\n| 2 |\r\n| 3 |\r\n");
	cs += _T("describes (w x h) rect areas: (1 x 4), (2 x 3), (2 x 2), (3 x 1)\r\n");
	
	cs += _T("\r\n---------- psuedo code\r\n");

	cs += _T("\r\nloop (columns,0]\r\n");
	cs += _T("\tif column height greater than prev column height\r\n");
	cs += _T("\t\tincrement counts for heights [0,prev column height)\r\n");
	cs += _T("\t\tset counts for heights [prev column height, column height) to 1\r\n");
	cs += _T("\telse\r\n");
	cs += _T("\t\tincrement counts for heights [0,column height - 1]\r\n");
	cs += _T("\t\tevalute max rects [column height,prev column height - 1]\r\n");
	cs += _T("\tevalute max rects [0,first column height - 1]\r\n");

	cs += _T("\r\n---------- speedups\r\n");

	cs += _T("\r\nlook for a run of equal height columns as if we maintain run length and column height no need to increment counts");
	
	return cs;
}

CString leetcodeproblem4::gettitle(void)const
{
	CString cs;
	cs += CString("4");
	return cs;
}

CString leetcodeproblem4::getdifficulty(void)const
{
	CString cs;
	cs += CString("hard");
	return cs;
}

CString leetcodeproblem4::getsubmissions(void)const
{
	CString cs;
	cs += _T("6.2M");
	return cs;
}

CString leetcodeproblem4::getacceptancerate(void)const
{
	CString cs;
	cs += _T("39.5%");
	return cs;
}

CString leetcodeproblem4::getruntimerank(void)const
{
	CString cs;
	cs += _T("top 24.11");
	return cs;
}

CString leetcodeproblem4::getmemoryrank(void)const
{
	CString cs;
	cs += _T("top 5.91%");
	return cs;
}

CString leetcodeproblem4::getdescription(void)const
{
	CString cs;
	cs += _T("leetcode4:Median of Two Sorted Arrays\r\n");
	cs += _T("\r\n");
	cs += _T("Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.\r\n");
	cs += _T("\r\n");
	cs += _T("Constraints:\r\n");
	cs += _T("\r\n");
	cs += _T("nums1.length == m\r\n");
	cs += _T("nums2.length == n\r\n");
	cs += _T("0 <= m <= 1000\r\n");
	cs += _T("0 <= n <= 1000\r\n");
	cs += _T("1 <= m + n <= 2000\r\n");
	cs += _T("-10^6 <= nums1[i], nums2[i] <= 10^6\r\n");
	cs += _T("\r\n");
	cs += _T("The overall run time complexity should be O(log (m+n)).");

	return cs;
}

CString leetcodeproblem4::getexamplesdescription(void)const
{
	CString cs;
	cs += _T("Example 1:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: nums1 = {1,3}, nums2 = {2}\r\n");
	cs += _T("Output: 2.00000\r\n");
	cs += _T("Explanation:\r\n");
	cs += _T("merged array = [1,2,3] and median is 2.\r\n");
	
	cs += _T("\r\n");
	cs += _T("Example 2:\r\n");
	cs += _T("\r\n");
	cs += _T("Input: nums1 = {1,2}, nums2 = {3,4}\r\n");
	cs += _T("Output: 2.50000\r\n");
	cs += _T("merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.");
	
	return cs;
}

CString leetcodeproblem4::getrundescription(void)const
{
	std::vector<std::vector<int>> vNums1 = {
											{1,3},		// 2 Explanation: merged array = {1,2,3} and median is 2.
											{1,2},		// 2.5 Explanation: merged array = {1,2,3,4} and median is (2 + 3) / 2 = 2.5.
											{1,1},		// 1 Explanation: merged array = {1,1,1,2} and median is (1 + 1) / 2 = 1.
											{1,2}		// 1 Explanation: merged array = {1,1,1,2} and median is (1 + 1) / 2 = 1.
										  };
	std::vector<std::vector<int>> vNums2 = {
											{2},
											{3,4},
											{1,2},
											{1,1}
										  };

	Solution sl;
	CString cs;
	auto i = vNums1.cbegin(),end=vNums1.cend();
	auto j = vNums2.cbegin();
	for(;i!=end;++i,++j)
	{
		if(std::distance(vNums1.cbegin(),i))
			cs += _T("\r\n\r\n");
					
		std::vector<int> nums1=*i;
		std::vector<int> nums2=*j;
		const auto d = sl.findMedianSortedArrays(nums1,nums2);
			CString csL;
		csL.Format(_T("Example %li:\r\n\r\nInput: nums1 = %s, nums2 = %s\r\nOutput: %f"),std::distance(vNums1.cbegin(),i)+1,getszformat(*i),getszformat(*j),d);
		cs += csL;
	}
	return cs;
}

CString leetcodeproblem4::getreasoningdescription(void)const
{
	// NOTES
	// 
	// Imagine building one sorted vector ( o ) from the two sorted vectors ( i, j )
	// Do this by appending to 'o' the min(i[nI],j[nJ]), if used 'i' increment nI else increment nJ
	// As 'o' is progresively build built check if we have enough data to determine 'o's median return it
	// That is the approach ( but we dont build an output vector as there is no need )

	// PSUEDO CODE
	// 
	// output median position = ( i.length + j.length ) / 2
	// loop nI<i.length AND nJ<j.length
	//		increment output length
	//		if i[nI] < j[nJ]
	//			increment nI
	//		else
	//			increment nJ
	//		if increment output length > output median position
	//			return ( output[median position] + output[median position - 1] ) / 2
	//
	// loop nI<i.length
	//		increment output length
	//		increment nI
	//		if increment output length > output median position
	//			return ( output[median position] + output[median position - 1] ) / 2
	//
	// loop nJ<j.length
	//		increment output length
	//		increment nJ
	//		if increment output length > output median position
	//			return ( output[median position] + output[median position - 1] ) / 2

	// above assumes 'i' and 'j' are same size and length > 1, actual code handles all cases
	
	// SPEED UPS
	// 
	// speedup:
	//		we dont build the 'output' vector so cache last two values that would have been appended to it
	
	CString cs;

	cs += _T("\r\n---------- notes\r\n");

	cs += _T("\r\nImagine building one sorted vector ( o ) from the two sorted vectors ( i, j )\r\n");
	cs += _T("Do this by appending to 'o' the min(i[nI],j[nJ]), if used 'i' increment nI else increment nJ\r\n");
	cs += _T("As 'o' is progresively build built check if we have enough data to determine 'o's median return it\r\n");
	cs += _T("That is the approach ( but we dont build an output vector as there is no need )\r\n");

	cs += _T("\r\n---------- psuedo code\r\n");

	cs += _T("\r\noutput median position = ( i.length + j.length ) / 2\r\n");
	cs += _T("loop nI<i.length AND nJ<j.length\r\n");
	cs += _T("\tincrement output length\r\n");
	cs += _T("\tif i[nI] < j[nJ]\r\n");
	cs += _T("\t\tincrement nI\r\n");
	cs += _T("\telse\r\n");
	cs += _T("\t\ttincrement nI\r\n");
	cs += _T("\tif increment output length > output median position\r\n");
	cs += _T("\t\treturn ( output[median position] + output[median position - 1] ) / 2\r\n");
	cs += _T("\r\nloop nI<i.length\r\n");
	cs += _T("\tincrement output length\r\n");
	cs += _T("\tincrement nI\r\n");
	cs += _T("\tif increment output length > output median position\r\n");
	cs += _T("\t\treturn ( output[median position] + output[median position - 1] ) / 2\r\n");
	cs += _T("\r\nloop nJ<j.length\r\n");
	cs += _T("\tincrement output length\r\n");
	cs += _T("\tincrement nJ\r\n");
	cs += _T("\tif increment output length > output median position\r\n");
	cs += _T("\t\treturn ( output[median position] + output[median position - 1] ) / 2\r\n");

	cs += _T("\r\nabove assumes 'i' and 'j' are same size and length > 1, actual code handles all cases\r\n");

	cs += _T("\r\n---------- speedups\r\n");

	cs += _T("\r\nwe dont build the 'output' vector so cache last two values that would have been appended to it");
	
	return cs;
}
