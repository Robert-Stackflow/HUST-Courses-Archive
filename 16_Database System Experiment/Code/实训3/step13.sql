-- 13) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、
--     保险表(insurance)、基金表(fund)和投资资产表(property)，
--     列出所有客户的编号、名称和总资产，总资产命名为total_property。
--     总资产为储蓄卡余额，投资总额，投资总收益的和，再扣除信用卡透支的金额
--     (信用卡余额即为透支金额)。客户总资产包括被冻结的资产。
--    请用一条SQL语句实现该查询：

select c_id,c_name,(coalesce(pall_amount,0)+coalesce(iall_amount,0)+coalesce(fall_amount,0)+coalesce(ball_amount,0)-coalesce(b2all_amount,0)) as total_property from client left outer join
(select pro_c_id,sum(pro_quantity*p_amount+pro_income) from finances_product,property where p_id=pro_pif_id and pro_type=1 group by pro_c_id) as pall(pall_c_id,pall_amount) on(pall_c_id=c_id) left outer join
(select pro_c_id,sum(pro_quantity*i_amount+pro_income) from insurance,property where i_id=pro_pif_id and pro_type=2 group by pro_c_id) as iall(iall_c_id,iall_amount) on(iall_c_id=c_id) left outer join
(select pro_c_id,sum(pro_quantity*f_amount+pro_income) from fund,property where f_id=pro_pif_id and pro_type=3 group by pro_c_id) as fall(fall_c_id,fall_amount) on(fall_c_id=c_id) left outer join
(select b_c_id,sum(b_balance)from bank_card where b_type='储蓄卡' group by b_c_id) as ball(ball_c_id,ball_amount) on(ball_c_id=c_id) left outer join
(select b_c_id,sum(b_balance)from bank_card where b_type='信用卡' group by b_c_id) as b2all(b2all_c_id,b2all_amount) on(b2all_c_id=c_id)
order by c_id;






/*  end  of  your code  */ 