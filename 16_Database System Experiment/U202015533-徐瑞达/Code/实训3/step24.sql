      -- 24) 查询任意两个客户的相同理财产品数
--   请用一条SQL语句实现该查询：
with base_user_list as(
select pro_c_id as base_c_id from (select pro_c_id,pro_pif_id from property where pro_type=1 group by pro_c_id,pro_pif_id order by pro_c_id) group by pro_c_id having count(pro_pif_id)>=2
),base_pif_list as(
	select base_c_id,pro_pif_id from base_user_list,property where pro_type=1 and pro_c_id=base_c_id
),base_common_list as(
	select t1.base_c_id t1_c_id,t2.base_c_id t2_c_id,t1.pro_pif_id t1_pif_id,t2.pro_pif_id t2_pif_id from(base_pif_list as t1 cross join base_pif_list as t2) where t1.base_c_id!=t2.base_c_id and t1.pro_pif_id=t2.pro_pif_id
)
select t1_c_id as pro_c_id,t2_c_id as pro_c_id,count(*) as total_count from base_common_list group by t1_c_id,t2_c_id  having count(*)>=2 order by t1_c_id;
--/*  end  of  your code  */