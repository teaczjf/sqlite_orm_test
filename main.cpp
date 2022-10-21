#include <QCoreApplication>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include "sqlorm_xpro_define.h"
#include <sqlite_orm.h>
#include "my_easylogging.h"

using namespace sqlite_orm;
using namespace std;

using std::cout;
using std::endl;
using std::string;


const string db_file = R"(./db.sqlite)";

int main ( int argc, char *argv[] )
{

    QCoreApplication a ( argc, argv );
    LOG ( INFO ) << "111111111111";

    SQLORM_XPRO_DEVINFO TJ_GSCJ_DEVINFO;
    auto storage = make_storage ( db_file,
                                  make_table ( "SQLORM_XPRO_DEVINFO",
                                          make_column ( "ID", &SQLORM_XPRO_DEVINFO::ID, primary_key() ),
                                          //    make_column("DEV_NAME", &SQLORM_XPRO_DEVINFO::DEV_NAME),
                                          make_column ( "DEV_NAME", &SQLORM_XPRO_DEVINFO::DEV_NAME, unique() ),

                                          make_column ( "DEV_CMD_TABLE_NAME", &SQLORM_XPRO_DEVINFO::DEV_CMD_TABLE_NAME ),
                                          make_column ( "COMUNITATE_MODE", &SQLORM_XPRO_DEVINFO::COMUNITATE_MODE ),
                                          make_column ( "TCP_IP", &SQLORM_XPRO_DEVINFO::TCP_IP ),
                                          make_column ( "TCP_PORT", &SQLORM_XPRO_DEVINFO::TCP_PORT ),
                                          make_column ( "UDP_IP_SRC", &SQLORM_XPRO_DEVINFO::UDP_IP_SRC ),
                                          make_column ( "UDP_PORT_SRC", &SQLORM_XPRO_DEVINFO::UDP_PORT_SRC ),
                                          make_column ( "UDP_IP_DST", &SQLORM_XPRO_DEVINFO::UDP_IP_DST ),
                                          make_column ( "UDP_PORT_DST", &SQLORM_XPRO_DEVINFO::UDP_PORT_DST ),
                                          make_column ( "UDPMC_IP", &SQLORM_XPRO_DEVINFO::UDPMC_IP ),
                                          make_column ( "UDPMC_IP_TX", &SQLORM_XPRO_DEVINFO::UDPMC_IP_TX ),
                                          make_column ( "UDPMC_PORT_TX", &SQLORM_XPRO_DEVINFO::UDPMC_PORT_TX ),
                                          make_column ( "UDPMC_IP_RX", &SQLORM_XPRO_DEVINFO::UDPMC_IP_RX ),
                                          make_column ( "UDPMC_PORT_RX", &SQLORM_XPRO_DEVINFO::UDPMC_PORT_RX ) ) );
    storage.sync_schema(); //同步数据库
    //清空表格
    // storage.remove_all<SQLORM_XPRO_DEVINFO>();
    // storage.remove_all<Department>();
    // storage.remove_all<Employee>();

    // 插入数据方法1 使用replace 如果主键相同，就更新 如果不存在就插入
    cout << "replace 1" << endl;

    storage.replace ( SQLORM_XPRO_DEVINFO{1, "James", "James", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston"} );
    cout << "replace 2" << endl;
    storage.replace ( SQLORM_XPRO_DEVINFO{2, "James11", "James", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston"} );
    cout << "replace 3" << endl;
    storage.replace ( SQLORM_XPRO_DEVINFO{2, "James", "James1111", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston"} );

    // 插入数据方法2 使用insert 如果主键不是数字，就无法插入？
    TJ_GSCJ_DEVINFO.ID = 3;
    TJ_GSCJ_DEVINFO.DEV_NAME = "TJ_GSCJ";
    TJ_GSCJ_DEVINFO.DEV_CMD_TABLE_NAME = "TJ_GSCJ_CMDTABLE";
    TJ_GSCJ_DEVINFO.COMUNITATE_MODE = "TCP_SERVER";
    TJ_GSCJ_DEVINFO.TCP_IP = "127.0.0.1";
    TJ_GSCJ_DEVINFO.TCP_PORT = "5000";
    TJ_GSCJ_DEVINFO.UDP_IP_SRC = "Jameqs";
    TJ_GSCJ_DEVINFO.UDP_PORT_SRC = "Jameqs";
    TJ_GSCJ_DEVINFO.UDP_PORT_DST = "Jameqs";
    TJ_GSCJ_DEVINFO.UDP_IP_DST = "Jameqs";
    TJ_GSCJ_DEVINFO.UDPMC_IP = "Jameqs";
    TJ_GSCJ_DEVINFO.UDPMC_IP_RX = "Jameqs";
    TJ_GSCJ_DEVINFO.UDPMC_IP_TX = "Jameqs";
    TJ_GSCJ_DEVINFO.UDPMC_PORT_RX = "Jameqs";
    TJ_GSCJ_DEVINFO.UDPMC_PORT_TX = "Jameqs";

    // TJ_GSCJ_DEVINFO = "";
    // 插两条
    LOG ( ERROR ) << "111111111";

    auto commited = storage.transaction ( [&]() mutable {
        try
        {

            // storage.replace(SQLORM_XPRO_DEVINFO{3, "James", "James1111", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston", "Houston"});
            // LOG(ERROR) << "222222222";

            // storage.insert(TJ_GSCJ_DEVINFO);
            LOG ( ERROR ) << "333333333333333333";
            for ( int i = 0; i < 100000; i++ ) {
                TJ_GSCJ_DEVINFO.DEV_NAME = to_string ( i );
                storage.insert ( TJ_GSCJ_DEVINFO );
            }
            LOG ( ERROR ) << "4444444444444";
        } catch ( const std::system_error &e )
        {
            LOG ( ERROR ) << "insert FAILE" << e.what();
            return false; //  exits lambda and calls ROLLBACK
        }
        //  exits lambda and calls COMMIT
        return true; } );

    LOG ( ERROR ) << "222222222";

    if ( commited == true ) {
        cout << "Commited successfully, go on." << endl;
    } else {
        cout << "Commit failed, process an error" << endl;
    }

    return a.exec();
}
