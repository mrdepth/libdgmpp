//
//  Rate.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public protocol TimeRate {
	typealias Value = Int
	var value: Value {get set}
	static var rate: (Int, Int) {get}
}

public extension TimeRate {
}

public struct Seconds: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public static let rate = (1, 1)
}

public struct Milliseconds: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public static let rate = (1, 1000)
}

public struct Minutes: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public static let rate = (60, 1)
}

public struct Hours: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public static let rate = (3600, 1)
}

public protocol Scalable {
	func scale(_ s: Double) -> Self
}

extension Int: Scalable {
	public func scale(_ s: Double) -> Int {
		return self * Int(s)
	}
}

extension Double: Scalable {
	public func scale(_ s: Double) -> Double {
		return self * s
	}
}

extension Float: Scalable {
	public func scale(_ s: Double) -> Float {
		return self * Float(s)
	}
}

public struct Rate<Value, Ratio> where Value: Scalable, Ratio: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public init<Ratio2>(_ rate: Rate<Value, Ratio2>) {
		value = rate.value.scale(Double(Ratio.rate.0 * Ratio2.rate.1) / Double(Ratio.rate.1 * Ratio2.rate.0))
	}
	
	public static func*<Ratio2>(lhs: Rate<Value, Ratio>, rhs: Ratio2) -> Value where Ratio2: TimeRate{
		return lhs.value.scale(Double(rhs.value) * Double(Ratio.rate.1 * Ratio2.rate.0) / Double(Ratio.rate.0 * Ratio2.rate.1))
	}
}
