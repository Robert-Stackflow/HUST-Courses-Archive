     -- 23) 查找相似的理财产品
--   请用一条SQL语句实现该查询：
select pro_pif_id,count(*) as cc,dense_rank()over(order by cc desc) as prank from property where pro_type=1 and pro_pif_id in
(select pro_pif_id from(
select pro_pif_id,dense_rank() over(order by pro_quantity desc) as rank from property where pro_type=1 and pro_c_id in
(select pro_c_id from property where pro_type=1 and pro_pif_id=14) and pro_pif_id!=14) where rank<=3) group by pro_pif_id order by pro_pif_id;

--/*  end  of  your code  */