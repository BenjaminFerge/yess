#include "sqlite_projection_repo.hpp"
#include "../../log.hpp"

namespace yess::db
{
Sqlite_projection_repo::Sqlite_projection_repo(std::string conn_key,
                                               std::string conn_str)
    : Sqlite_repository(conn_key, conn_str)
{
    init_db();
}
void Sqlite_projection_repo::create(Projection p)
{
    std::string sql = "INSERT INTO projections(type, data) VALUES(?, ?)";
    SQLite::Statement stmt(*db_, sql);

    stmt.bind(1, p.data);
    stmt.bind(2, p.type);
    stmt.exec();

    log::info("Projection created successfully");
}
std::vector<Projection> Sqlite_projection_repo::all()
{
    std::string sql = "SELECT id, type, data FROM projections";
    SQLite::Statement stmt(*db_, sql);

    std::vector<Projection> result;
    while (stmt.executeStep()) {
        int id = stmt.getColumn(0);
        std::string type = stmt.getColumn(1);
        std::string data = stmt.getColumn(2);

        Projection s = {id, type, data};
        result.push_back(s);
    }
    log::info("Retrieved all projections successfully");
    return result;
}
Projection Sqlite_projection_repo::id(int id)
{
    std::string sql = "SELECT type, data "
                      "FROM projections "
                      "WHERE id = ?";

    SQLite::Statement stmt(*db_, sql);

    stmt.bind(1, id);
    stmt.exec();

    std::string type = stmt.getColumn(0);
    std::string data = stmt.getColumn(1);

    Projection projection = {id, type, data};
    log::info("Retrieved projection by ID '{}' successfully", id);
    return projection;
}
std::vector<Projection> Sqlite_projection_repo::type(std::string t)
{
    std::string sql = "SELECT id, type, data FROM projections WHERE type = ?";
    SQLite::Statement stmt(*db_, sql);
    stmt.bind(1, t);

    std::vector<Projection> result;
    while (stmt.executeStep()) {
        int id = stmt.getColumn(0);
        std::string type = stmt.getColumn(1);
        std::string data = stmt.getColumn(2);

        Projection s = {id, type, data};
        result.push_back(s);
    }
    log::info("Retrieved projections for type '{}' successfully", t);
    return result;
}
Projection Sqlite_projection_repo::remove(int id)
{
    std::string sql = "DELETE FROM projections WHERE id = ?";
    SQLite::Statement stmt(*db_, sql);

    stmt.bind(1, id);
    stmt.exec();

    log::info("Projection deleted successfully");
}
} // namespace yess::db
