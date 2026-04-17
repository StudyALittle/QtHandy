-- ----------------------------
---- 目录分组表 SQLite
-- ----------------------------
create table if not exists "dir_group" (
    "id" integer primary key autoincrement,
    "parent_id" integer not null default 0,
    "name" varchar(255) not null,
    "sort" integer not null default 0,
    "description" varchar(255),
    "create_time" datetime not null default (datetime('now','localtime')),
    "update_time" datetime not null default (datetime('now','localtime'))
);
