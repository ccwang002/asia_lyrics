source("namelist.R")
library(base64enc)
library(XML)
library(RSQLite)
get_album <- function(url) {
  doc <- htmlParse(url)
  doc.select <- doc["//dd[span/@class='hc1'][span/@class='hc2'][span/@class='hc3'][span/a/@href]"]
  doc.select <- doc.select[sapply(doc.select, function(dd) {
    index.album_name <- which(sapply(dd["span"], xmlAttrs) == "hc1")
    tmp <- dd["span"][[index.album_name]]["a"]
    length(tmp) >= 1
  })]
  lapply(doc.select, function(dd) {
    index.album_name <- which(sapply(dd["span"], xmlAttrs) == "hc1")
    tmp <- dd["span"][[index.album_name]]["a"]
    tmp <- xmlAttrs(tmp[[1]])
    href <- sprintf("http://mojim.com%s", tmp["href"])
    title <- tmp["title"]
    meta <- toString.XMLNode(dd["span"][[which(sapply(dd["span"], xmlAttrs) == "hc2")]])
    songs <- sprintf("%s%s", toString.XMLNode(dd["span"][[which(sapply(dd["span"], xmlAttrs) == "hc3")]]), toString.XMLNode(dd["span"][[which(sapply(dd["span"], xmlAttrs) == "hc4")]]))
    list(href=href, title=title, meta=meta, songs=songs)
  })
}
get_lyrics_raw <- function(url) {
  doc <- htmlParse(url)
  sapply(doc["//table"], toString.XMLNode)
}
db <- dbConnect("SQLite", "mojim.db")
if (!dbExistsTable(db, "mojim")) dbGetQuery(db, "CREATE TABLE mojim ( href TEXT PRIMARY KEY, name TEXT, title TEXT, meta TEXT, songs TEXT, lyrics_raw TEXT)")
library(hash)
hreflist <- readRDS("hreflist.Rds")
encode <- function(src) {
  base64encode(charToRaw(src))
}
decode <- function(src) {
  rawToChar(base64decode(src))
}

for(i in seq_along(namelist)) {
  res <- dbGetQuery(db, sprintf("SELECT name FROM name WHERE name = '%s'", namelist[i]))
  if (nrow(res) > 0) next
  name <- encode(names(namelist)[i])
  album <- get_album(namelist[i])
  is_query <- FALSE
  for(j in seq_along(album)) {
    href <- album[[j]]$href
    check_href <- dbGetQuery(db, sprintf("SELECT href FROM mojim WHERE href='%s'", href))
#    if (nrow(check_href) > 0) {
   if (isTRUE(hreflist[[href]])) {
      print(sprintf("href: %s is exsisted", href))
      next
    }
    is_query <- TRUE
    title <- encode(album[[j]]$title)
    meta <- encode(album[[j]]$meta)
    songs <- encode(album[[j]]$songs)
    lyrics_raw <- encode(paste(get_lyrics_raw(href), collapse=""))
    sql <- sprintf("INSERT INTO mojim (href, name, title, meta, songs, lyrics_raw) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", href, name, title, meta, songs, lyrics_raw)
    dbGetQuery(db, sql)
    hreflist[[href]] <- TRUE
    print(sprintf("%s href: %s inserted", format(Sys.time()), href))
  }
  if (is_query) {
    gc()
  }
  cat(sprintf("%d,%d\n", i, length(namelist)))
  dbGetQuery(db, sprintf("INSERT INTO name (name) VALUES ('%s')", namelist[i]))
  Sys.sleep(10)
}
dbDisconnect(db)
