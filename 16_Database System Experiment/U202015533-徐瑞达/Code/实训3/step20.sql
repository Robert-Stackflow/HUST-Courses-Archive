 -- 20) 查询销售总额前三的理财产品
--   请用一条SQL语句实现该查询：
select pyear,rk,p_id,sumamount from
(select date_part as pyear,rank() over(partition by pyear order by sumamount desc)as rk,p_id,sumamount from
((select date_part('year',pro_purchase_time),p_id,sum(pro_quantity*p_amount) as sumamount from property,finances_product where pro_type=1 and pro_pif_id=p_id and (date_part('year',pro_purchase_time)=2010) group by p_id,date_part('year',pro_purchase_time)) union
(select date_part('year',pro_purchase_time),p_id,sum(pro_quantity*p_amount) as sumamount from property,finances_product where pro_type=1 and pro_pif_id=p_id and (date_part('year',pro_purchase_time)=2011) group by p_id,date_part('year',pro_purchase_time)))) where rk>=1;


--/*  end  of  your code  */