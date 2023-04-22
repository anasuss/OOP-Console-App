package managementOfStudentAbsences;

import java.sql.*;

public class DBConnection {
  private Connection conn;
  private String url = "jdbc:sqlserver://DESKTOP-FN78GLK\\SQLEXPRESS;Database=managementOfStudentAbsences;IntegratedSecurity=true;encrypt=true;trustServerCertificate=true" ;    	
  public DBConnection() {
    try {
      conn = DriverManager.getConnection(url);
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
  
  public Connection getConnection() {
    return conn;
  }
  
  public void close() {
    try {
      if (conn != null) {
        conn.close();
      }
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}
