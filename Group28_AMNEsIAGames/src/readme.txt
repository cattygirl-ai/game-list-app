To run the database_test:
    g++ database.cpp database_test.cpp -lsqlite3 -c
    g++ database.o database_test.o -lsqlite3 -o tdb
    ./tdb

To run the login_handler test:
    g++ database.cpp login_handler.cpp login_handler_test.cpp -lsqlite3 -c
    g++ database.o login_handler.o login_handler_test.o -lsqlite3 -o tc
    ./tlh

NOTE: If the database test is ran more than once, some test cases will say fail
(ex. creating a new user would say fail, because the user already exists). To avoid
this, you can remove the whole database (no important data is stored in it currently)
using:
    rm amnesiaGames.db
