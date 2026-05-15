-- ----------------------------
---- 目录分组表拥有的目录 SQLite
-- ----------------------------
create table if not exists "dir_group_dir" (
    "id" integer primary key autoincrement,
    "group_id" integer not null default 0,
    "dir_path" varchar(255) not null,
    "sort" integer not null default 0,
    "name" varchar(255) not null,
    "description" varchar(255),
    "create_time" datetime not null default (datetime('now','localtime')),
    "update_time" datetime not null default (datetime('now','localtime'))
);
