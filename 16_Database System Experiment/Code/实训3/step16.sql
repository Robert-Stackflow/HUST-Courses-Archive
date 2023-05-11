-- 16) 查询持有相同基金组合的客户对，如编号为A的客户持有的基金，编号为B的客户也持有，反过来，编号为B的客户持有的基金，编号为A的客户也持有，则(A,B)即为持有相同基金组合的二元组，请列出这样的客户对。为避免过多的重复，如果(1,2)为满足条件的元组，则不必显示(2,1)，即只显示编号小者在前的那一对，这一组客户编号分别命名为c_id1,c_id2。

-- 请用一条SQL语句实现该查询：

select c_id1,c_id2 from (select c_id from client) as t1(c_id1),(select c_id as c_id2 from client) as t2(c_id2) where not exists (select pro_pif_id from ((SELECT pro_pif_id FROM property WHERE pro_type=3 and pro_c_id=c_id1 group by pro_pif_id)union all(SELECT pro_pif_id FROM property WHERE pro_type=3 and pro_c_id=c_id2 group by pro_pif_id)) group by pro_pif_id having count(*) < 2) and exists(select pro_pif_id from ((SELECT pro_pif_id FROM property WHERE pro_type=3 and pro_c_id=c_id1 group by pro_pif_id)union all(SELECT pro_pif_id FROM property WHERE pro_type=3 and pro_c_id=c_id2 group by pro_pif_id)) group by pro_pif_id) and c_id1 <c_id2;

/*  end  of  your code  */