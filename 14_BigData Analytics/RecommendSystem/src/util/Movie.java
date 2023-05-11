package util;

public class Movie implements Comparable<Movie> {

    int movieId;
    String title;
    String genres;
    String[] tags;

    public Movie() {
    }

    public Movie(int movieId, String title, String genres) {
        this.movieId = movieId;
        if (title.contains("\""))
            this.title = title.split("\"")[1];
        else
            this.title = title;
        this.genres = genres;
        this.tags = genres.split("\\|");
    }

    public int getMovieId() {
        return movieId;
    }

    public void setMovieId(int movieId) {
        this.movieId = movieId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getGenres() {
        return genres;
    }

    public void setGenres(String genres) {
        this.genres = genres;
    }

    public String[] getTags() {
        return tags;
    }

    public void setTags(String[] tags) {
        this.tags = tags;
    }

    @Override
    public String toString() {
        return "Movie{" + "movieId=" + movieId + ", title='" + title + '\'' + ", genres='" + genres + '\'' + '}';
    }

    @Override
    public int compareTo(Movie o) {
        return getMovieId() - o.getMovieId();
    }
}
