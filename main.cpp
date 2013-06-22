/* 
 * File:   main.cpp
 * Author: grill
 *
 * Created on 22 czerwiec 2013, 16:25
 */


/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

//connection configuration
#include "db_conf.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << endl;
    cout << "Wynik zapytania: 'select CustomerID, CompanyName, City from customers order by City'..." << endl;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        
        //create connection string 
        string socket;
        socket = "tcp://";
        socket += HOST;
        socket += ':';
        socket += PORT;
        
        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(socket, USERNAME, PASSWORD);
        /* Connect to the MySQL test database */
        con->setSchema(DBNAME);

        stmt = con->createStatement();
        res = stmt->executeQuery("select CustomerID, CompanyName, City from customers order by City");
        while (res->next()) {
            //cout << res->getRow();
            cout << "[CustomerID]: ";
            cout << res->getString("CustomerID");
            cout << ",  [CompanyName]: ";
            cout << res->getString("CompanyName");
            cout << ",  [City]: ";            
            /* Access column data by alias or column name */
            cout << res->getString("City") << endl;
        }
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return 0;
}

