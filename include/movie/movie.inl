std::ostream& operator<<(std::ostream& os, const Movie& m)
{
    os << " { " << m.data->id << " | " << m.data->primaryTitle << " | " << m.data->originalTitle << " } ";
    return os;
}
