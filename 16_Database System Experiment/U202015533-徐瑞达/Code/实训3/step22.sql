    -- 22) 查询购买了所有畅销理财产品的客户
--   请用一条SQL语句实现该查询：
select c_id as pro_c_id from client where not exists(
select * from ((select peek.pro_pif_id from
	(select pro_pif_id from property where pro_type=1 group by pro_pif_id 				having count(pro_pif_id)>2) peek(pro_pif_id) left outer join
	(select pro_c_id,pro_pif_id as id2 from property where pro_type=1) as cli (pro_c_id,pro_pif_id) on peek.pro_pif_id=cli.pro_pif_id where cli.pro_c_id=c_id)
	union all
	(select pro_pif_id from property where pro_type=1 group by pro_pif_id having count(pro_pif_id)>2)) group by pro_pif_id having count(*)<=1
);
--/*  end  of  your code  */