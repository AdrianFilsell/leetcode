
#pragma once

#include <vector>
#include <memory>
#include <numeric>
#include <string>
#include <algorithm>

class leetcodeproblem
{
public:
	leetcodeproblem(){}
	virtual ~leetcodeproblem(){}
	virtual CString gettitle(void)const=0;
	virtual CString getdifficulty(void)const=0; // easy, medium, hard
	virtual CString getsubmissions(void)const=0;
	virtual CString getacceptancerate(void)const=0;
	virtual CString getruntimerank(void)const=0;
	virtual CString getmemoryrank(void)const=0;
	virtual CString getdescription(void)const=0;
	virtual CString getexamplesdescription(void)const=0;
	virtual CString getrundescription(void)const=0;
	virtual CString getreasoningdescription(void)const=0;
protected:
	CString getszformat(const std::vector<int>& v)const
	{
		CString cs(_T("{"));
		auto i = v.cbegin(),end=v.cend();
		for(;i!=end;++i)
		{
			if(std::distance(v.cbegin(),i))
				cs += _T(",");

			CString csL;
			csL.Format(_T("%li"),*i);
			cs += csL;
		}
		cs += _T("}");
		return cs;
	}
};

class leetcodeproblem1799 : public leetcodeproblem
{
public:
	leetcodeproblem1799(){}
	virtual CString gettitle(void)const override;
	virtual CString getdifficulty(void)const override;
	virtual CString getsubmissions(void)const override;
	virtual CString getacceptancerate(void)const override;
	virtual CString getruntimerank(void)const override;
	virtual CString getmemoryrank(void)const override;
	virtual CString getdescription(void)const override;
	virtual CString getexamplesdescription(void)const override;
	virtual CString getrundescription(void)const override;
	virtual CString getreasoningdescription(void)const override;

class Solution {
public:
    int maxScore(std::vector<int>& nums)
	{
		const gcdmatrix m(nums);
		gcdnumvector vNums(nums);
		const int nMultiplier=static_cast<int>(nums.size()/2);
		unsigned short vCache[7*0x3fff];
		memset(vCache,0,sizeof(unsigned short)*0x3fff*7); // max 7 levels, max 14 numbers
		return getmax(vCache,m,vNums,0,nMultiplier);
	}
protected:
	struct gcdmatrix
	{
		gcdmatrix(){m_pElements=nullptr;}
		gcdmatrix(const std::vector<int>& nums)
		{
			m_nDim=static_cast<int>(nums.size());
			m_pElements=new int[m_nDim*m_nDim];
			for(int nC=0;nC<m_nDim;++nC)
				for(int nR=0;nR<nC;++nR)
				{
					const int n=std::gcd(nums[nC],nums[nR]);
					set(nC,nR,n);
					set(nR,nC,n);
				}
		}
		~gcdmatrix()
		{
			delete[] m_pElements;
		}
		void set(const int nC,const int nR,const int n){m_pElements[m_nDim*nR+nC]=n;}
		int get(const int nC,const int nR)const{return m_pElements[m_nDim*nR+nC];}
		int m_nDim;
		int *m_pElements;
	};
	struct gcdnum
	{
		gcdnum(){}
		gcdnum(const int nIdx)
		{
			m_nIdx=nIdx;
		}
		int m_nIdx;
	};
	struct gcdnumvector
	{
		gcdnumvector(){}
		gcdnumvector(const std::vector<int>& nums)
		{
			m_v.resize(nums.size());
			auto i=nums.cbegin(),end=nums.cend();
			auto j=m_v.begin();
			for(int n=0;i!=end;++i,++j,++n)
				(*j)=gcdnum(n);
		}
		std::vector<gcdnum> m_v;
	};
	inline int getmax(unsigned short *pCache,const gcdmatrix& m,gcdnumvector& v,const int nIndices,const int nMultiplier)const
	{
		// nIndices<=0x3fff

		{
			// https://www.geeksforgeeks.org/memoization-1d-2d-and-3d/
			const auto i=pCache[(nMultiplier-1)*0x3fff+nIndices];
			if(i)
				return i;
		}

		if(nMultiplier==1)
		{
			// one pair left
			int nValid=0;
			int pairidx[2];
			auto i=v.m_v.begin(),end=v.m_v.end();
			for(;i!=end&&nValid<2;++i)
			{
				const auto iIdx=(1<<(*i).m_nIdx);
				if(nIndices&iIdx)continue;
				pairidx[nValid++]=(*i).m_nIdx;
			}
			const int nGCD=m.get(pairidx[0],pairidx[1]);
			return nGCD;
		}
		
		int nMax=0;
		auto i=v.m_v.begin(),end=v.m_v.end();
		for(;i!=end;++i)
		{
			const auto iIdx=(1<<(*i).m_nIdx);
			if(nIndices&iIdx)continue;
			
			auto j=i;
			for(++j;j!=end;++j)
			{
				const auto jIdx=(1<<(*j).m_nIdx);
				if(nIndices&jIdx)continue;
				
				const int nGCD=m.get((*i).m_nIdx,(*j).m_nIdx);
				const int nLocal=(nMultiplier*nGCD)+getmax(pCache,m,v,nIndices|(iIdx|jIdx),nMultiplier-1);
				if(nLocal>nMax)
					nMax=nLocal;
			}
		}

		pCache[(nMultiplier-1)*0x3fff+nIndices]=nMax;
				
		return nMax;
	}
};
};

class leetcodeproblem1807 : public leetcodeproblem
{
public:
	leetcodeproblem1807(){}
	virtual CString gettitle(void)const override;
	virtual CString getdifficulty(void)const override;
	virtual CString getsubmissions(void)const override;
	virtual CString getacceptancerate(void)const override;
	virtual CString getruntimerank(void)const override;
	virtual CString getmemoryrank(void)const override;
	virtual CString getdescription(void)const override;
	virtual CString getexamplesdescription(void)const override;
	virtual CString getrundescription(void)const override;
	virtual CString getreasoningdescription(void)const override;

class Solution {
public:
    std::string evaluate(const std::string s, std::vector<std::vector<std::string>>& k)
	{
		std::sort(k.begin(),k.end(),[](const std::vector<std::string>& lhs,const std::vector<std::string>& rhs)->bool
											{
												auto cmp = lhs[0]<rhs[0];
												return cmp;
											});

		std::string r;
		size_t nOff=0,nFrom,nContentFrom=0,nContentInclusiveTo=-1;
		while((nFrom=s.find('(',nOff))!=-1)
		{
			nContentInclusiveTo = nFrom-1;
			r += std::string(s,nContentFrom,(nContentInclusiveTo-nContentFrom+1));
			
			const size_t nInclusiveTo=s.find(')',nFrom+1);
			if(nInclusiveTo==-1)
				break;
			nContentFrom = nInclusiveTo+1;

			const std::string sKey(s,nFrom+1,(nInclusiveTo-nFrom+1)-2);
			const auto i=std::lower_bound(k.begin(),k.end(),std::vector<std::string>{},[&sKey](const std::vector<std::string>& lhs,const std::vector<std::string>& rhs)->bool
										{
											auto cmp = lhs[0]<sKey;
											return cmp;
										});
			if(i==k.cend()||(*i)[0]!=sKey)
				r += "?";
			else
				r += (*i)[1];
			nOff=nContentFrom;
		}
		nContentInclusiveTo=s.length();
		r += std::string(s,nContentFrom,(nContentInclusiveTo-nContentFrom+1));
		
		return r;
	}
};
protected:
	CString getszformat(const std::vector<std::vector<std::string>>& v)const
	{
		CString cs;
		cs += _T("[");
		auto i = v.cbegin(),end=v.cend();
		for(;i!=end;++i)
		{
			if(std::distance(v.cbegin(),i))
				cs += _T(",");

			cs += _T("[");
			auto j = (*i).cbegin(),end=(*i).cend();
			for(;j!=end;++j)
			{
				if(std::distance((*i).cbegin(),j))
					cs += _T(",");

				cs += CString(_T("\""));
				cs += CStringA((*j).c_str());
				cs += CString(_T("\""));
			}
			cs += _T("]");
		}
		cs += _T("]");
		return cs;
	}
};

class leetcodeproblem1793 : public leetcodeproblem
{
public:
	leetcodeproblem1793(){}
	virtual CString gettitle(void)const override;
	virtual CString getdifficulty(void)const override;
	virtual CString getsubmissions(void)const override;
	virtual CString getacceptancerate(void)const override;
	virtual CString getruntimerank(void)const override;
	virtual CString getmemoryrank(void)const override;
	virtual CString getdescription(void)const override;
	virtual CString getexamplesdescription(void)const override;
	virtual CString getrundescription(void)const override;
	virtual CString getreasoningdescription(void)const override;

class Solution {
public:
    int maximumScore(std::vector<int>& nums, int k) {
        
		// think of k as the split position

		const int nNums=static_cast<int>(nums.size());
		int i=k,j=k,min=nums[k],max=min;
		while(i>0 && j<(nNums-1))
		{
			if(nums[i-1]<nums[j+1])
			{
				// look for a better 'j'
				++j;
				
				// update min
				if(nums[j]<min)
					min=nums[j];
			}
			else
			{
				// look for a better 'i'
				--i;

				// update min
				if(nums[i]<min)
					min=nums[i];
			}

			// update max
			const auto n=(j-i+1)*min;
			if(n>max)
				max=n;
		}
		for(--i;i>-1;--i)
		{
			// update min
			if(nums[i]<min)
				min=nums[i];

			// update max
			const auto n=(nNums-i)*min;
			if(n>max)
				max=n;
		}
		for(++j;j<nNums;++j)
		{
			// update min
			if(nums[j]<min)
				min=nums[j];
			
			// update max
			const auto n=(j+1)*min;
			if(n>max)
				max=n;
		}
		return max;
	}
};
};

class leetcodeproblem84 : public leetcodeproblem
{
public:
	leetcodeproblem84(){}
	virtual CString gettitle(void)const override;
	virtual CString getdifficulty(void)const override;
	virtual CString getsubmissions(void)const override;
	virtual CString getacceptancerate(void)const override;
	virtual CString getruntimerank(void)const override;
	virtual CString getmemoryrank(void)const override;
	virtual CString getdescription(void)const override;
	virtual CString getexamplesdescription(void)const override;
	virtual CString getrundescription(void)const override;
	virtual CString getreasoningdescription(void)const override;

class Solution {
public:

int largestRectangleArea(std::vector<int>& heights) {

		// sliding window i column in width
		int arrWindow[10000];
		int nWindowHeight=0;
		
		int nMax=0,nEqualHeights=0;
		auto iHeight=heights.crbegin(),end=heights.crend();
		const int nHeights=static_cast<int>(heights.size());
		if(nHeights==0)
			return 0;
		for(int nHeightIndex=nHeights-1;iHeight!=end;++iHeight,--nHeightIndex)
		{
			const int nHeight=*iHeight;
			int nPrevWindowHeight=nWindowHeight;

			// update window runs
			if(nPrevWindowHeight==nHeight)
			{
				++nEqualHeights;
			}
			else
			{
				if(nEqualHeights)
				{
					for(int n=0;n<nPrevWindowHeight;++n)
						arrWindow[n]+=nEqualHeights;
					nEqualHeights=0;
				}
				if(nPrevWindowHeight<nHeight)
				{
					// top of column
					const int nTop = nHeight-nPrevWindowHeight;
					for(int n=0;n<nTop;++n)
						arrWindow[nHeight-1-n]=1;
					
					// remainder
					const int nRemainder = nHeight-nTop;
					for(int n=0;n<nRemainder;++n)
						++arrWindow[n];
				}
				else
				{
					// remainder
					for(int n=0;n<nHeight;++n)
						++arrWindow[n];
			
					// max
					const int nTop = nPrevWindowHeight-nHeight;
					for(int n=0;n<nTop;++n)
						if(arrWindow[nPrevWindowHeight-n-1]*(nPrevWindowHeight-n)>nMax)
							nMax=arrWindow[nPrevWindowHeight-n-1]*(nPrevWindowHeight-n);
				}
			}
			nWindowHeight=nHeight;
		}

		// max
		for(int n=0;n<heights[0];++n)
			if((arrWindow[n]+nEqualHeights)*(n+1)>nMax)
				nMax=(arrWindow[n]+nEqualHeights)*(n+1);

		return nMax;
	}
};
};

class leetcodeproblem4 : public leetcodeproblem
{
public:
	leetcodeproblem4(){}
	virtual CString gettitle(void)const override;
	virtual CString getdifficulty(void)const override;
	virtual CString getsubmissions(void)const override;
	virtual CString getacceptancerate(void)const override;
	virtual CString getruntimerank(void)const override;
	virtual CString getmemoryrank(void)const override;
	virtual CString getdescription(void)const override;
	virtual CString getexamplesdescription(void)const override;
	virtual CString getrundescription(void)const override;
	virtual CString getreasoningdescription(void)const override;

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        
		const int m=static_cast<int>(nums1.size());
		const int n=static_cast<int>(nums2.size());

		if(m==0)
		{
			if(n%2)
				return nums2[n/2];
			return ( nums2[n/2] + nums2[(n/2)-1] ) / 2.0;
		}
		else
		if(n==0)
		{
			if(m%2)
				return nums1[m/2];
			return ( nums1[m/2] + nums1[(m/2)-1] ) / 2.0;
		}

		auto iM=nums1.cbegin(),iN=nums2.cbegin();
		int nFromM=0,nFromN=0,nA,nMid=(n+m)/2,nSum=0;
		bool bM=(*iM)<(*iN),bA=false,bAB=((n+m)%2)==0,bMValid=true,bNValid=true;
		int nMinSum=bAB?nMid:nMid+1;
		while(bMValid&&bNValid)
		{
			int nVal,nNums;
			if(bM)
			{
				nVal=*iM;
				auto i = std::upper_bound(iM,nums1.cend(),nVal); // first item greater then 'value'
				const int nNextFrom = static_cast<int>(std::distance(nums1.cbegin(),i));
				nNums = nNextFrom-nFromM;
				iM=i;
				if(iM==nums1.cend())
				{
					bM=false;
					bMValid=false;
				}
				else
				if(bNValid)
					bM=(*iM)<(*iN);
				nFromM=nNextFrom;
			}
			else
			{
				nVal=*iN;
				auto i = std::upper_bound(iN,nums2.cend(),nVal); // first item greater then 'value'
				const int nNextFrom = static_cast<int>(std::distance(nums2.cbegin(),i));
				nNums = nNextFrom-nFromN;
				iN=i;
				if(iN==nums2.cend())
				{
					bM=true;
					bNValid=false;
				}
				else
				if(bMValid)
					bM=(*iM)<(*iN);
				nFromN=nNextFrom;
			}
			nSum+=nNums;
			if(nSum<nMinSum)
				continue;
			if(bAB)
			{
				if(bA)
				{
					if(nMid<nSum)
						return (nVal+nA)/2.0;
				}
				else
				{
					if(nMid<nSum)
						return nVal;
					bA=true;
					nA=nVal;
				}
			}
			else
				return nVal;
		}
		while(bMValid)
		{
			int nVal,nNums;
			{
				nVal=*iM;
				auto i = std::upper_bound(iM,nums1.cend(),nVal); // first item greater then 'value'
				const int nNextFrom = static_cast<int>(std::distance(nums1.cbegin(),i));
				nNums = nNextFrom-nFromM;
				iM=i;
				nFromM=nNextFrom;
			}
			nSum+=nNums;
			if(nSum<nMinSum)
				continue;
			if(bAB)
			{
				if(bA)
				{
					return (nVal+nA)/2.0;
				}
				else
				{
					if(nMid<nSum)
						return nVal;
					bA=true;
					nA=nVal;
				}
			}
			else
				return nVal;
		}
		while(bNValid)
		{
			int nVal,nNums;
			{
				nVal=*iN;
				auto i = std::upper_bound(iN,nums2.cend(),nVal); // first item greater then 'value'
				const int nNextFrom = static_cast<int>(std::distance(nums2.cbegin(),i));
				nNums = nNextFrom-nFromN;
				iN=i;
				nFromN=nNextFrom;
			}
			nSum+=nNums;
			if(nSum<nMinSum)
				continue;
			if(bAB)
			{
				if(bA)
				{
					return (nVal+nA)/2.0;
				}
				else
				{
					if(nMid<nSum)
						return nVal;
					bA=true;
					nA=nVal;
				}
			}
			else
				return nVal;
		}

		return 0;
    }
};
};
