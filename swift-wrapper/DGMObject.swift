//
//  DGMObject.swift
//  dgmpp
//
//  Created by Artem Shimanski on 26.12.2017.
//

import Foundation
import cwrapper

fileprivate struct WeakReference<Value: AnyObject> {
    weak var value: Value?
}

fileprivate var handles: [dgmpp_handle: WeakReference<DGMObject>] = [:]

public class DGMObject {
	var handle: dgmpp_handle
    
    static func get<T: DGMObject>(_ handle: dgmpp_handle, orCreate block: () -> T) -> T {
        if let value = handles[handle]?.value as? T {
            return value
        }
        else {
            return block()
//            let value = block()
//            handles[handle] = WeakReference(value: value)
//            return value
        }
    }
	
	required init(_ handle: dgmpp_handle) {
		self.handle = handle
        handles[handle] = WeakReference(value: self)
	}
	
	deinit {
        handles[handle] = nil
        dgmpp_release(handle)
	}
	
}


extension DGMObject: Hashable {
	
	public func hash(into hasher: inout Hasher) {
		hasher.combine(handle)
	}
	
	public static func ==(lhs: DGMObject, rhs: DGMObject) -> Bool {
		return lhs.handle == rhs.handle
	}
}

