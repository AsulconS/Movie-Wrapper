std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    os << "( ";
    for(const auto& s : v)
        os << s << ' ';
    os << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const Movie& m)
{
    os << " { " << m.data->id << " | "
                << m.data->type << " | "
                << m.data->primaryTitle << " | "
                << m.data->originalTitle << " | "
                << m.data->isAdult << " | "
                << m.data->startYear << " | "
                << m.data->endYear << " | "
                << m.data->runtimeMinutes << " | "
                << m.data->genders << " } ";
    return os;
}
