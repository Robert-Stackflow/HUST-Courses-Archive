import java.sql.*;

public class Transform {
  static final String JDBC_DRIVER = "org.postgresql.Driver";
    static final String DB_URL = "jdbc:postgresql://127.0.0.1:5432/postgres?";
    static final String USER = "gaussdb";
    static final String PASS = "Passwd123@123";
		static final String cols[]={"chinese","math","english","physics","chemistry","biology","history","geography","politics"};
    
    /**
     * 向sc表中插入数据
     *
     */
    public static int insertSC(Connection connection,int sno,String col_name,String col_value){
try{
	String sql="insert into sc(sno,col_name,col_value)values(?,?,?)";
PreparedStatement statement=connection.prepareStatement(sql);
statement.setInt(1,sno);
statement.setString(2,col_name);
statement.setString(3,col_value);
statement.executeUpdate();
return 0;
			}catch(SQLException e){
				e.printStackTrace();
				return -1;
			}
    }

    public static void main(String[] args) {
			try{
Class.forName(JDBC_DRIVER);
Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
Statement statement=connection.createStatement();
ResultSet result=statement.executeQuery("select * from entrance_exam");
while(result.next()){
	int sno=result.getInt("sno");
	for(String col:cols){
		String str=result.getString(col);
		if(str!=null)
			insertSC(connection,sno,col,str);
	}
}
			}
			catch(ClassNotFoundException e){
				e.printStackTrace();
			}catch(SQLException e){
				e.printStackTrace();
			}
    }
}