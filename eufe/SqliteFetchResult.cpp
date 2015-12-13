#include "SqliteFetchResult.h"

using namespace eufe;

SqliteFetchResult::SqliteFetchResult(const std::shared_ptr<SqliteFetchRequest>& request): request_(request)
{
}

SqliteFetchResult::~SqliteFetchResult(void)
{
	finalize();
}

		
bool SqliteFetchResult::next()
{
	auto stmt = request_->getStmt();
	return stmt && sqlite3_step(stmt) == SQLITE_ROW;
}

int SqliteFetchResult::getInt(int columnIndex)
{
	auto stmt = request_->getStmt();
	return sqlite3_column_int(stmt, columnIndex);
}

double SqliteFetchResult::getDouble(int columnIndex)
{
	auto stmt = request_->getStmt();
	return sqlite3_column_double(stmt, columnIndex);
}

std::string SqliteFetchResult::getText(int columnIndex)
{
	auto stmt = request_->getStmt();
	return reinterpret_cast<const char*>(sqlite3_column_text(stmt, columnIndex));
}

Blob SqliteFetchResult::getBlob(int columnIndex)
{
	auto stmt = request_->getStmt();
	size_t size = sqlite3_column_bytes(stmt, columnIndex);
	const void* blob = sqlite3_column_blob(stmt, columnIndex);
	return Blob(blob, size);
}

void SqliteFetchResult::finalize()
{
	auto stmt = request_->getStmt();
	if (stmt) {
		sqlite3_clear_bindings(stmt);
		sqlite3_reset(stmt);
	}
}