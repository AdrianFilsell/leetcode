
#pragma once

class hint
{
public:
	enum type {t_null=0x0,							// null
			   t_problem=0x1,						// problem changed
			  };
	hint():hint(t_null){}
	hint(const type t):m_Type(t){}
	type gettype(void)const{return m_Type;}
	
	hint& operator=(const hint& o) {m_Type=o.m_Type;return *this;}
protected:
	type m_Type;
};
