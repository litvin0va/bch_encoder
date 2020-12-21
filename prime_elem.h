polynom get_nullifying_polynom (const polynom &p, const polynom &mod); ///find f : f(p)=0 (mod)
polynom get_nullifying_product (const std::vector<polynom> &vec, const polynom &mod);

std::vector<polynom> create_power_vector (const polynom &pol, int max_deg, const polynom &mod);


polynom find_prime (const polynom &factor);
void gener_prime_polynoms (int max_size);
std::vector<polynom> create_power_vector (const polynom &pol, int max_deg);
