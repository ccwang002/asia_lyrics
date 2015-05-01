## Asia Lyrics

### Setup

Install Python 3.4+ environment, recommend Anaconda 3.

```
conda install ipython-notebook pandas matplotlib
ipython notebook
```

Extract the parsed database (if you want to handle the raw database, it's the same procedure)

```
tar xf parsed_lyrics.tar.xz
```

### Play / Develop

Create / Look at `*.ipynb` files.


### Parsed Database schema

Should be self-explained. It's quite redundant now but I'm fine with that.

```
# output of .schema
CREATE TABLE albums (
    href             TEXT PRIMARY KEY,
    title            TEXT,
    singer           TEXT,
    year             TEXT,
    lang             TEXT
);
CREATE TABLE songs (
    href             TEXT PRIMARY KEY,
    album_href       TEXT,
    album_title      TEXT,
    album_lang       TEXT,
    singer           TEXT,
    year             INTEGER,
    song             TEXT,
    song_writer      TEXT,
    lyrics_writer    TEXT,
    lyrics           TEXT,
    FOREIGN KEY(album_href) REFERENCES albums(href)
);
```
