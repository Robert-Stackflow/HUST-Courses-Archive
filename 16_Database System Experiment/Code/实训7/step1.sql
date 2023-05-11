--创建触发器函数TRI_INSERT_FUNC()
CREATE OR REPLACE FUNCTION TRI_INSERT_FUNC() RETURNS TRIGGER AS
$$
DECLARE
   	declare msg char(128);
	declare p_type integer;
	declare pif_id integer;
BEGIN
    p_type:=new.pro_type;
	pif_id:=new.pro_pif_id;
	if p_type=1 then
		if pif_id not in (select p_id from finances_product) then
			raise exception '%',concat(concat('finances product #',pif_id),' not found!');
		end if;
	elseif p_type=2 then
		if pif_id not in (select i_id from insurance) then
			raise exception '%',concat(concat('insurance #',pif_id),' not found!');
		end if;
	elseif p_type=3 then
		if pif_id not in (select f_id from fund) then
			raise exception '%',concat(concat('fund #',pif_id),' not found!');
		end if;
	else
		raise exception '%',concat(concat('type ',p_type),' is illegal!');
	end if;
   --触发器业务结束
   return new;--返回插入的新元组
END;
$$ LANGUAGE PLPGSQL;


-- 创建before_property_inserted触发器，使用函数TRI_INSERT_FUNC实现触发器逻辑：
CREATE  TRIGGER before_property_inserted BEFORE INSERT ON property
FOR EACH ROW
EXECUTE PROCEDURE TRI_INSERT_FUNC();

















