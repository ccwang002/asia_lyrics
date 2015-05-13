## Asia Lyrics

### Setup

Install Python 3.4+ environment, recommend [Miniconda 3]. After miniconda installed, run the command below to install required packages.

```sh
conda install ipython-notebook pandas matplotlib sqlalchemy seaborn
```

Extract the parsed database (if you want to handle the raw database, do the same thing for `raw_data/mojim.tar.xz`)

```sh
tar xf parsed_lyrics.tar.xz
# or on Windows `tar` command may not exist, then use
python -m tarfile -e parsed_lyrics.tar.xz
```

> ### Optional but may be useful setups
> More usage about `conda` [here][conda].
> 
> Use [conda virtual environment](http://conda.pydata.org/docs/intro.html#creating-python-3-4-or-python-2-6-environments) to prevent polluting your system setting.
> 
> ```sh
> $ conda create -n lyrics python=3.4 ipython-notebook  ...  # pkgs here
> $ activate lyrics
> (lyrics)$ ipython notebook
> (lyrics)$ ...
> (lyrics)$ deactivate  # after works are done
> $
> ```

[Miniconda 3]: http://conda.pydata.org/miniconda.html
[conda]: http://conda.pydata.org/docs/

### Play / Develop

Launch the IPython notebook server by running the following command at this repo directory.

```sh
ipython notebook
```

It automatically launches a web browser at <http://localhost:8888>. Then one can now create or look at existed `*.ipynb` files.


### Parsed Database schema

Should be self-explained. It's quite redundant now but I'm fine with that.

```sql
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
