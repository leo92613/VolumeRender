#pragma once

#include <Hawk/Math/Functions.hpp>
#include <array>


namespace Hawk {
	namespace Math {

		class Plane {
		public:
			constexpr Plane() = default;
			constexpr Plane(Math::Vec3 const& normal, F32 offset);
			constexpr Plane(Math::Vec4 const& v);
			constexpr Plane(F32 a, F32 b, F32 c, F32 d);
			constexpr Plane(Math::Vec3 const& a, Math::Vec3 const& b, Math::Vec3 const& c);
			constexpr auto SetNormal(Math::Vec3 const& normal) noexcept->void;
			constexpr auto SetOffset(F32 offset)               noexcept->void;
			constexpr auto Normal() const noexcept->Math::Vec3 const&;
			constexpr auto Offset() const noexcept->F32;;
		private:
			Math::Vec3 m_Normal = Math::Vec3(0.0f, 1.0f, 0.0f);
			F32        m_Offset = 0.0f;
		};

		class Ray {
		public:
			constexpr Ray() = default;
			constexpr Ray(Math::Vec3 position, Math::Vec3 direction);
			constexpr auto SetPosition(Math::Vec3 const& position)   noexcept->void;
			constexpr auto SetDirection(Math::Vec3 const& direction) noexcept->void;
			constexpr auto Position()  const noexcept->Math::Vec3 const&;
			constexpr auto Direction() const noexcept->Math::Vec3 const&;

		private:
			Math::Vec3 m_Position  = Math::Vec3(0.0f, 0.0f, 0.0f);
			Math::Vec3 m_Direction = Math::Vec3(0.0f, 1.0f, 0.0f);

		};

		class Sphere {
		public:
			constexpr Sphere() = default;
			constexpr Sphere(Math::Vec3 const& center, F32 radius) noexcept;
			constexpr Sphere(F32 x, F32 y, F32 z, F32 radius)      noexcept;
			constexpr auto SetCenter(Math::Vec3 const &v) noexcept->void;
			constexpr auto SetCenter(F32 x, F32 y, F32 z) noexcept->void;
			constexpr auto SetRadius(F32 &r)              noexcept->void;
			constexpr auto Center() const noexcept->Math::Vec3 const&;
			constexpr auto Radius() const noexcept->F32;

		private:
			Math::Vec3 m_Center = Math::Vec3(0.0f, 0.0f, 0.0f);
			F32        m_Radius = 1.0f;
		};

		class Box {
		public:
			constexpr Box() = default;
			constexpr Box(Math::Vec3 const& min, Math::Vec3 const& max) noexcept;
			constexpr auto SetMinExtends(Math::Vec3 const &v) noexcept->void;
			constexpr auto SetMaxExtends(Math::Vec3 const &v) noexcept->void;
			constexpr auto SetMinExtends(F32 x, F32 y, F32 z) noexcept->void;
			constexpr auto SetMaxExtends(F32 x, F32 y, F32 z) noexcept->void;

			constexpr auto MinExtends() const noexcept->Math::Vec3 const&;
			constexpr auto MaxExtends() const noexcept->Math::Vec3 const&;

		private:
			Math::Vec3 m_MinExtends = Math::Vec3(0.0f, 0.0f, 0.0f);
			Math::Vec3 m_MaxExtends = Math::Vec3(0.0f, 0.0f, 0.0f);

		};

		class Frustum {
		public:
			enum Section { Near, Far, Left, Right, Top, Bottom };
		public:
			constexpr Frustum() = default;
			constexpr Frustum(Math::Mat4x4 const& proj) noexcept;
			constexpr auto SetPlane(Frustum::Section section, Math::Plane const& plane) noexcept -> void;
			constexpr auto Plane(Frustum::Section section)   const noexcept -> Math::Plane const&;
			
		private:
			constexpr auto GenerateFromPerspective(F32 hTan, F32 vTan, F32 zNear, F32 zFar)                        noexcept -> void;
			constexpr auto GenerateFromOrthographic(F32 left, F32 right, F32 top, F32 bottom, F32 zNear, F32 zFar) noexcept -> void;
		private:
			Math::Plane m_Planes[6];
		};

	
		constexpr auto operator*(Mat4x4 const& lhs, Plane const& rhs)   noexcept -> Plane;
		constexpr auto operator*(Mat4x4 const& lhs, Ray const& rhs)     noexcept -> Ray;
		constexpr auto operator*(Mat4x4 const& lhs, Sphere const& rhs)  noexcept -> Sphere;
		constexpr auto operator*(Mat4x4 const& lhs, Box const& rhs)     noexcept -> Box;
		constexpr auto operator*(Mat4x4 const& lhs, Frustum const& rhs) noexcept -> Frustum;

		constexpr auto Intersects(Frustum const& lhs, Sphere const& rhs) noexcept -> bool;
		constexpr auto Intersects(Frustum const& lhs, Box    const& rhs) noexcept -> bool;


	}
}

namespace Hawk {
	namespace Math {

		ILINE constexpr Plane::Plane(Math::Vec3 const & normal, F32 offset) : m_Normal(normal), m_Offset(offset) { }

		ILINE constexpr Plane::Plane(Math::Vec4 const & v) : m_Normal(v.x, v.y, v.z), m_Offset(v.w) {}

		ILINE constexpr Plane::Plane(F32 a, F32 b, F32 c, F32 d) : Plane(Math::Vec3(a, b, c), d) {}

		ILINE constexpr Plane::Plane(Math::Vec3 const & a, Math::Vec3 const & b, Math::Vec3 const & c) {
			m_Normal = Math::Normalize(Math::Cross(b - a, c - a));
			m_Offset = -Math::Dot(m_Normal, a);
		}

		ILINE constexpr  auto Plane::SetNormal(Math::Vec3 const & normal) noexcept -> void {
			m_Normal = normal;
		}

		ILINE constexpr auto Plane::SetOffset(F32 offset) noexcept -> void {
			m_Offset = offset;
		}

		[[nodiscard]] ILINE constexpr auto Plane::Normal() const noexcept -> Math::Vec3 const & {
			return m_Normal;
		}

		[[nodiscard]] ILINE constexpr auto Plane::Offset() const noexcept -> F32 {
			return m_Offset;
		}

		ILINE constexpr Ray::Ray(Math::Vec3 position, Math::Vec3 direction) : m_Position(position), m_Direction(direction) {}

		ILINE constexpr auto Ray::SetPosition(Math::Vec3 const & position) noexcept -> void {
			m_Position = position;
		}

		ILINE constexpr auto Ray::SetDirection(Math::Vec3 const & direction) noexcept -> void {
			m_Direction = direction;
		}

		[[nodiscard]] ILINE constexpr auto Ray::Position() const noexcept -> Math::Vec3 const & {
			return m_Position;
		}

		[[nodiscard]] ILINE constexpr auto Ray::Direction() const noexcept -> Math::Vec3 const & {
			return m_Direction;
		}


		ILINE constexpr Sphere::Sphere(Math::Vec3 const & center, F32 radius) noexcept : m_Center(center), m_Radius(radius) {}

		ILINE constexpr Sphere::Sphere(F32 x, F32 y, F32 z, F32 radius) noexcept : m_Center(x, y, z), m_Radius(radius) {}

		ILINE constexpr auto Sphere::SetCenter(Math::Vec3 const & v) noexcept -> void {
			m_Center = v;
		}

		ILINE constexpr auto Sphere::SetCenter(F32 x, F32 y, F32 z) noexcept -> void {
			this->SetCenter(Math::Vec3(x, y, z));
		}

		ILINE constexpr auto Sphere::SetRadius(F32 & r) noexcept -> void {
			m_Radius = r;
		}

		[[nodiscard]] ILINE  constexpr auto Sphere::Center() const noexcept -> Math::Vec3 const & {
			return m_Center;
		}

		[[nodiscard]] ILINE constexpr auto Sphere::Radius() const noexcept -> F32 {
			return m_Radius;
		}
		
		ILINE constexpr Box::Box(Math::Vec3 const & min, Math::Vec3 const & max) noexcept : m_MinExtends(min), m_MaxExtends(max)	{}

		ILINE constexpr auto Box::SetMinExtends(Math::Vec3 const & v) noexcept -> void {
			m_MinExtends = v;
		}

		ILINE constexpr auto Box::SetMaxExtends(Math::Vec3 const & v) noexcept -> void {
			m_MaxExtends = v;
		}

		ILINE constexpr auto Box::SetMinExtends(F32 x, F32 y, F32 z) noexcept -> void {
			this->SetMinExtends(Math::Vec3(x, y, z));
		}

		ILINE constexpr auto Box::SetMaxExtends(F32 x, F32 y, F32 z) noexcept -> void {
			this->SetMaxExtends(Math::Vec3(x, y, z));
		}

		[[nodiscard]] ILINE  constexpr auto Box::MinExtends() const noexcept -> Math::Vec3 const & {
			return m_MinExtends;
		}

		[[nodiscard]] ILINE  constexpr auto Box::MaxExtends() const noexcept -> Math::Vec3 const & {
			return m_MaxExtends;
		}


		ILINE constexpr Frustum::Frustum(Math::Mat4x4 const & proj) noexcept {

		
			auto const rcpXX = 1.0f / proj(0, 0);
			auto const rcpYY = 1.0f / proj(1, 1);
			auto const rcpZZ = 1.0f / proj(2, 2);

		
			if (proj(3, 0) == 0.0f && proj(3, 1) == 0.0f && proj(3, 2) == 0.0f && proj(3, 3) == 1.0f) {
				
				auto const left   = (-1.0f - proj(0, 3)) * rcpXX;
				auto const right  = ( 1.0f - proj(0, 3)) * rcpXX;
				auto const top    = ( 1.0f - proj(1, 3)) * rcpYY;
				auto const bottom = (-1.0f - proj(1, 3)) * rcpYY;
				auto const front  = ( 0.0f - proj(2, 3)) * rcpZZ;
				auto const back   = ( 1.0f - proj(2, 3)) * rcpZZ;

				if (front < back)
					GenerateFromOrthographic(left, right, top, bottom, front, back);
				else
					GenerateFromOrthographic(left, right, top, bottom, back, front);
			} else {
				
				if (rcpZZ > 0.0f)   {
					auto const farClip  = proj(2, 3) * rcpZZ;
					auto const nearClip = farClip / (rcpZZ + 1.0f);
					GenerateFromPerspective(rcpXX, rcpXX, farClip, nearClip);
				} else {
					auto const nearClip = proj(2, 3) * rcpZZ;
					auto const farClip = nearClip / (rcpZZ + 1.0f);
					GenerateFromPerspective(rcpXX, rcpXX, farClip, nearClip);
				}
			}
		}

		ILINE constexpr auto Frustum::SetPlane(Frustum::Section section, Math::Plane const& plane) noexcept -> void {
			m_Planes[static_cast<uint8_t>(section)] = plane;
		}
		
		[[nodiscard]] ILINE constexpr auto Frustum::Plane(Frustum::Section section) const noexcept -> Math::Plane const & {
			return m_Planes[static_cast<uint8_t>(section)];
		}

		
		[[nodiscard]] ILINE constexpr auto Intersects(Frustum const& lhs, Sphere const & rhs) noexcept -> bool {

			for (auto index = 0; index < 6; index++) {
				auto const& e = lhs.Plane(static_cast<Math::Frustum::Section>(index));
				if (Math::Dot(e.Normal(), rhs.Center()) + e.Offset() <= -rhs.Radius())
					return false;
			}
	
			return true;
		}

		[[nodiscard]] ILINE constexpr auto Intersects(Frustum const& lhs, Box const& rhs)  noexcept -> bool {

			for (auto index = 0; index < 6; index++) {
				auto const& e = lhs.Plane(static_cast<Math::Frustum::Section>(index));
				auto const d = Math::Max(rhs.MinExtends().x * e.Normal().x, rhs.MaxExtends().x * e.Normal().x) +
							   Math::Max(rhs.MinExtends().y * e.Normal().y, rhs.MaxExtends().y * e.Normal().y) +
							   Math::Max(rhs.MinExtends().z * e.Normal().z, rhs.MaxExtends().z * e.Normal().z) + e.Offset();
				if (d < 0)
					return false;
			}
			return true;
		}
		ILINE constexpr auto Frustum::GenerateFromPerspective(F32 hTan, F32 vTan, F32 zNear, F32 zFar) noexcept -> void {

		    auto const nearX = hTan * zNear;
			auto const nearY = vTan * zNear;
			auto const farX  = hTan * zFar;
			auto const farY  = vTan * zFar;

			
			auto const nHx = 1.0f / Math::Sqrt(1.0f + hTan * hTan);
			auto const nHz = -nHx * hTan;
			auto const nVy = 1.0f / Math::Sqrt(1.0f + vTan * vTan);
			auto const nVz = -nVy * vTan;

			m_Planes[Section::Near]   = Math::Plane(0.0f, 0.0f,-1.0f,-zNear);
			m_Planes[Section::Far]    = Math::Plane(0.0f, 0.0f, 1.0f, zFar);
			m_Planes[Section::Left]   = Math::Plane(nHx,  0.0f, nHz, 0.0f);
			m_Planes[Section::Right]  = Math::Plane(-nHx, 0.0f, nHz, 0.0f);
			m_Planes[Section::Top]    = Math::Plane(0.0f,-nVy,  nVz, 0.0f);
			m_Planes[Section::Bottom] = Math::Plane(0.0f, nVy,  nVz, 0.0f);


		}
		ILINE constexpr auto Frustum::GenerateFromOrthographic(F32 left, F32 right, F32 top, F32 bottom, F32 front, F32 back) noexcept -> void {
			m_Planes[Section::Near]   = Math::Plane(0.0f, 0.0f, -1.0f, -front);
			m_Planes[Section::Far]    = Math::Plane(0.0f, 0.0f, 1.0f,  back);
			m_Planes[Section::Left]   = Math::Plane(1.0f, 0.0f, 0.0f, -left);
			m_Planes[Section::Right]  = Math::Plane(-1.0f, 0.0f, 0.0f, right);
			m_Planes[Section::Top]    = Math::Plane(0.0f, -1.0f, 0.0f, bottom);
			m_Planes[Section::Bottom] = Math::Plane(0.0f, 1.0f, 0.0f, -top);

		}

		ILINE constexpr auto Hawk::Math::operator*(Mat4x4 const& lhs, Plane const& rhs) noexcept -> Plane {
			return Math::Transpose(Math::Inverse(lhs)) *  Math::Vec4(rhs.Normal(), rhs.Offset());
		}
		ILINE constexpr auto operator*(Mat4x4 const& lhs, Ray const& rhs) noexcept -> Ray {
			return Ray();
		}
		ILINE constexpr auto operator*(Mat4x4 const& lhs, Sphere const& rhs) noexcept -> Sphere {
			auto const center = lhs * Hawk::Math::Vec4(rhs.Center(), 1.0f);
			return Sphere(center.x, center.y, center.z, rhs.Radius());
		}
		ILINE constexpr auto operator*(Mat4x4 const& lhs, Box const& rhs) noexcept -> Box {	  
			auto const min = lhs * Hawk::Math::Vec4(rhs.MinExtends(), 1.0f);
			auto const max = lhs * Hawk::Math::Vec4(rhs.MaxExtends(), 1.0f);
			return Box(Math::Vec3(min.x, min.y, min.z), Math::Vec3(max.x, max.y, max.z));
		}
		ILINE constexpr auto operator*(Mat4x4 const& lhs, Frustum const& rhs) noexcept -> Frustum {

			auto result = Frustum{};
			auto const trans  = Math::Transpose(Math::Inverse(lhs));
			for (auto index = 0; index < 6; index++) {
				auto const& e = rhs.Plane(static_cast<Math::Frustum::Section>(index));
				result.SetPlane(static_cast<Math::Frustum::Section>(index), Math::Plane(trans * Math::Vec4(e.Normal(), e.Offset())));
			}
			return result;
		}
	}
}