   -- 21) 投资积极且偏好理财类产品的客户
--   请用一条SQL语句实现该查询：
select ptable.pro_c_id as pro_c_id from
(
	(select pro_c_id,count(pro_c_id)as pcount from
		(select pro_c_id from property,finances_product where pro_type=1 
			and pro_pif_id=p_id group by pro_c_id,p_id order by pro_c_id)
	group by pro_c_id) as ptable(pro_c_id,pcount) left outer join
	(select pro_c_id,count(pro_c_id)as fcount from
		(select pro_c_id from property,fund where pro_type=3 
			and pro_pif_id=f_id group by pro_c_id,f_id order by pro_c_id)
	group by pro_c_id) as ftable(pro_c_id,fcount)
on ptable.pro_c_id=ftable.pro_c_id) where pcount>=3 and pcount>fcount order by pro_c_id;

-- select pro_c_id from
-- ,(select pro_c_id from property,fund where pro_type=1 and pro_pif_id=f_id group by pro_c_id,f_id order by pro_c_id)as ftable(f_c_id) group by pro_c_id order by pro_c_id) where pcount>=3;





--/*  end  of  your code  */