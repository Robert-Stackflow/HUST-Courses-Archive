-- 6) 查询资产表中所有资产记录里商品收益的众数和它出现的次数。
--    请用一条SQL语句实现该查询：


select pro_income,count(pro_income) as presence from property group by pro_income having count(pro_income) >= all(select count(pro_income) from property group by pro_income);


/*  end  of  your code  */