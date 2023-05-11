import java.sql.*;
import java.util.Scanner;

public class Transfer {
    static final String JDBC_DRIVER = "org.postgresql.Driver";
    static final String DB_URL = "jdbc:postgresql://127.0.0.1:5432/postgres?";
    static final String USER = "gaussdb";
    static final String PASS = "Passwd123@123";
    /**
     * 转账操作
     *
     * @param connection 数据库连接对象
     * @param sourceCard 转出账号
     * @param destCard 转入账号
     * @param amount  转账金额
     * @return boolean
     *   true  - 转账成功
     *   false - 转账失败
     */
    public static boolean transferBalance(Connection connection,
                             String sourceCard,
                             String destCard, 
                             double amount){
								 ResultSet result=null;
								 try{
                        connection.setAutoCommit(false);
                        String searchSql="select b_type,b_balance from bank_card where b_number=?";
                        String updateSql="update bank_card set b_balance=? where b_number=?";			
                        PreparedStatement statement=connection.prepareStatement(searchSql);
                        statement.setString(1,sourceCard);
                        result=statement.executeQuery();
                        String s_type=null;
                        Double s_balance=null;
                        while(result.next()){
                        s_type=result.getString("b_type");
                        s_balance=result.getDouble("b_balance");
                        }
                        statement=connection.prepareStatement(searchSql);
                        statement.setString(1,destCard);
                        result=statement.executeQuery();
                        String d_type=null;
                        Double d_balance=null;
                        while(result.next()){
                        d_type=result.getString("b_type");
                        d_balance=result.getDouble("b_balance");
                        }
                        // System.out.println(s_type!=null);
                        // System.out.println(d_type!=null);
                        // System.out.println(s_balance!=null);
                        // System.out.println(s_type!="信用卡");
                        // System.out.println(d_balance!=null);
                        // System.out.println(s_balance>amount);
                        if(s_type!=null&&s_balance!=null&&d_type!=null&&d_balance!=null&&
                        !s_type.contains("信用卡")&&s_balance>amount){
                            statement=connection.prepareStatement(updateSql);
                        statement.setDouble(1,s_balance-amount);
                        statement.setString(2,sourceCard);
                        statement.executeUpdate();
                            statement=connection.prepareStatement(updateSql);
                            if(d_type.contains("信用卡"))
                            statement.setDouble(1,d_balance-amount);
                            else
                        statement.setDouble(1,d_balance+amount);
                        statement.setString(2,destCard);
                        statement.executeUpdate();
                            connection.commit();
                            return true;
                        }
                        return false;
								 }catch(SQLException e){
									 e.printStackTrace();
									 try{
									 connection.rollback();
									 return false;
									 }catch(SQLException e2){
										 	e2.printStackTrace();
									 return false;
									 }
								 }
}

    // 不要修改main() 
    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        Class.forName(JDBC_DRIVER);

        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);

        while(sc.hasNext())
        {
            String input = sc.nextLine();
            if(input.equals(""))
                break;

            String[]commands = input.split(" ");
            if(commands.length ==0)
                break;
            String payerCard = commands[0];
            String  payeeCard = commands[1];
            double  amount = Double.parseDouble(commands[2]);
            if (transferBalance(connection, payerCard, payeeCard, amount)) {
              System.out.println("转账成功。" );
            } else {
              System.out.println("转账失败,请核对卡号，卡类型及卡余额!");
            }
        }
    }

}
