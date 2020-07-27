public class Fragment {
    public final Position starting, following;

    public Fragment(Position starting, Position following) {
        this.starting = starting;
        this.following = following;
    }

    public Position getStarting() {
        return starting;
    }

    @Override
    public String toString() {
        return starting.toString() + '-' + following.toString();
    }
}