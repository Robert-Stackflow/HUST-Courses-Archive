       -- 25) 查找相似的理财客户
--   请用一条SQL语句实现该查询：
select pac, pbc, common, crank from(select pac, pbc, common, row_number() over (partition by pac order by common desc, pbc) crank from(select t1.pro_c_id as pac, t2.pro_c_id as pbc, count(*) as common from property t1, property t2 where t1.pro_type = 1 and t2.pro_type = 1 and t1.pro_pif_id = t2.pro_pif_id and t1.pro_c_id != t2.pro_c_id group by pac, pbc))where crank < 3;

--/*  end  of  your code  */