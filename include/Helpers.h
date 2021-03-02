#ifndef HELPERS_H_
#define HELPERS_H_

#define DIGITAL_IO_PIN(pin) pin

#define DISABLE_COPY_AND_ASSIGN(Class) Class(const Class& x) = delete; Class& operator=(const Class x) = delete;
#define GET(type, var) type var() const { return m_##var; }
#define SET(type, var) void var(const type var) { m_##var = var; }
#define GET_SET(type, var) GET(type, var) SET(type, var)

#endif  // HELPERS_H_
